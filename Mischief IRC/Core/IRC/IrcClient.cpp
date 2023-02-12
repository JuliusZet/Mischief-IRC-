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
	Parse(data);
	return _ircSocket.SendData(data + '\n');
}

byte IrcClient::SendPrivmsg(string receiver, string text)
{
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

			Parse(message);
			Process(_messages.back());
		}
	}

	return 0;
}

byte IrcClient::Parse(string message)
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

	_messages.push_back(ircMessage);

	if (ircMessage.Command == "PRIVMSG" || ircMessage.Command == "JOIN" || ircMessage.Command == "PART" || (ircMessage.Command == "MODE" && ircMessage.Parameters.front().front() == '#'))
	{
		bool channelAlreadyExists = false;

		for (IrcChannel &channel : Channels)
		{
			if (channel.Name == ircMessage.Parameters.front())
			{
				channelAlreadyExists = true;
				channel.AddMessage(ircMessage);
				break;
			}
		}

		if (!channelAlreadyExists)
		{
			AddChannel(IrcChannel(ircMessage.Parameters.front()));

			Channels.back().AddMessage(ircMessage);
		}
	}

	else
	{
		bool channelAlreadyExists = false;

		for (IrcChannel& channel : Channels)
		{
			if (channel.Name == "IRC")
			{
				channelAlreadyExists = true;
				channel.AddMessage(ircMessage);
				break;
			}
		}

		if (!channelAlreadyExists)
		{
			AddChannel(IrcChannel("IRC"));
			Channels.back().AddMessage(ircMessage);
		}
	}

	return 0;
}

byte IrcClient::Process(IrcMessage ircMessage)
{
	if (ircMessage.Command == "PRIVMSG")
	{

	}

	else if (ircMessage.Command == "PING")
	{
		return Send("PONG :" + ircMessage.Parameters.front());
	}

	return 0;
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
