#include "pch.h"
#include "Core/IRC/IrcClient.h"

byte IrcClient::Connect(string host, string port, string pass, string nick, string user, string realname)
{
	if (_ircSocket.Connect(host, port) == 0)
	{
		if (Send("PASS :" + pass) == 0)
		{
			if (Send("NICK :" + nick) == 0)
			{
				_nick = nick;

				if (Send("USER " + user + " 0 * :" + realname) == 0)
				{
					_isConnected = true;

					_receiveThread = ReceiveAsync();
					_receiveThread.detach();
					
					return 0;
				}

				else
				{
					return 4;
				}
			}

			else
			{
				return 3;
			}
		}

		else
		{
			return 2;
		}

	}

	else
	{
		return 1;
	}
}

byte IrcClient::Disconnect(string quitMessage)
{
	if (_isConnected)
	{
		if (!quitMessage.empty())
		{
			Send("QUIT :" + quitMessage);
		}

		else
		{
			Send("QUIT");
		}

		if (_receiveThread.joinable())
		{
			_receiveThread.join();
		}

		_isConnected = false;
	}

	return _ircSocket.Disconnect();
}

byte IrcClient::Disconnect()
{
	return Disconnect("");
}

byte IrcClient::Reconnect(string quitMessage, string host, string port, string pass, string nick, string user, string realname)
{
	Disconnect(quitMessage);
	return Connect(host, port, pass, nick, user, realname);
}

byte IrcClient::Reconnect(string host, string port, string pass, string nick, string user, string realname)
{
	return Reconnect("", host, port, pass, nick, user, realname);
}

void IrcClient::AddChannel(IrcChannel ircChannel)
{
	Channels.push_back(ircChannel);
	OnNewChannel.InvokeFunctions(ircChannel);
}

byte IrcClient::Send(string data)
{
	return _ircSocket.SendData(data + '\n');
}

byte IrcClient::SendPrivmsg(string receiver, string text)
{
	Process(IrcMessage(_nick, "PRIVMSG", vector<string>{receiver, text}));
	return Send("PRIVMSG " + receiver + " :" + text);
}

byte IrcClient::Receive()
{
	string buffer = _ircSocket.ReceiveData();

	string message{};
	istringstream iStringStream{ buffer };

	while (getline(iStringStream, message))
	{
		if (!message.empty())
		{
			if (message.ends_with('\r'))
			{
				message.pop_back();
			}

			Process(Parse(message));
		}
	}

	return 0;
}

IrcMessage IrcClient::Parse(string message)
{
	IrcMessage ircMessage{};
	ircMessage.Time = system_clock::now();

	size_t currentPosStart{};
	size_t currentPosEnd{};

	// If the message has a prefix
	if (message.starts_with(':'))
	{

		// Get prefix
		currentPosEnd = message.find(' ', currentPosStart);
		ircMessage.Prefix = message.substr(1, currentPosEnd - 1);
		currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);
	}

	// Get command
	currentPosEnd = message.find(' ', currentPosStart);
	ircMessage.Command = message.substr(currentPosStart, currentPosEnd - currentPosStart);
	currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);

	// Get parameter(s)
	for (; currentPosStart != message.size() && currentPosEnd != string::npos; currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1))
	{
		if (message.at(currentPosStart) != ':')
		{
			currentPosEnd = message.find(' ', currentPosStart);
			ircMessage.Parameters.push_back(message.substr(currentPosStart, currentPosEnd - currentPosStart));
		}

		else
		{
			++currentPosStart;
			ircMessage.Parameters.push_back(message.substr(currentPosStart));
			break;
		}
	}

	return ircMessage;
}

byte IrcClient::Process(IrcMessage ircMessage)
{
	if (ircMessage.Command == "PRIVMSG")
	{

		// If it is a channel message or a direct message from us, add the message to a channel named after the receiver
		if (ircMessage.Parameters.front() != _nick)
		{
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// If it is a direct message for us, add the message to a direct message channel, named after the sender
		else
		{
			AddMessageToChannel(ircMessage, ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')));
		}
	}

	else if (ircMessage.Command == "JOIN")
	{

		// 1 channel
		if (ircMessage.Parameters.front().find(',') == string::npos)
		{
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// >= 2 channels
		else
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != ircMessage.Parameters.front().size() && currentPosEnd != string::npos; currentPosStart = ircMessage.Parameters.front().find_first_not_of(',', currentPosEnd + 1))
			{
				currentPosEnd = ircMessage.Parameters.front().find(',', currentPosStart);
				AddMessageToChannel(ircMessage, ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
			}
		}
	}

	else if (ircMessage.Command == "PART")
	{

		// 1 channel
		if (ircMessage.Parameters.front().find(',') == string::npos)
		{
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// >= 2 channels
		else
		{
			for (size_t currentPosStart{}, currentPosEnd{}; currentPosStart != ircMessage.Parameters.front().size() && currentPosEnd != string::npos; currentPosStart = ircMessage.Parameters.front().find_first_not_of(',', currentPosEnd + 1))
			{
				currentPosEnd = ircMessage.Parameters.front().find(',', currentPosStart);
				AddMessageToChannel(ircMessage, ircMessage.Parameters.front().substr(currentPosStart, currentPosEnd - currentPosStart));
			}
		}
	}

	else if (ircMessage.Command == "MODE")
	{

		// Channel mode
		if (ircMessage.Parameters.front().starts_with('#'))
		{
			AddMessageToChannel(ircMessage, ircMessage.Parameters.front());
		}

		// User mode
		else
		{
			AddMessageToChannel(ircMessage, "IRC");
		}
	}

	else if (ircMessage.Command == "PING")
	{
		return Send("PONG :" + ircMessage.Parameters.front());
	}

	else
	{
		AddMessageToChannel(ircMessage, "IRC");
	}

	return 0;
}

byte IrcClient::AddMessageToChannel(IrcMessage ircMessage, string channelName)
{
	for (IrcChannel& channel : Channels)
	{
		if (channel.Name == channelName)
		{
			channel.AddMessage(ircMessage);
			return 0;
		}
	}

	AddChannel(IrcChannel(channelName));
	Channels.back().AddMessage(ircMessage);

	return 1;
}

thread IrcClient::ReceiveAsync()
{
	return thread{ [this] {
		while (_isConnected)
		{
			Receive();
		}
	} };
}

bool IrcClient::IsConnected()
{
	return _isConnected;
}
