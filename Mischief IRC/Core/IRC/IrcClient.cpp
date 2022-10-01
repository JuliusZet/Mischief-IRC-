#include "pch.h"
#include "Core/IRC/IrcClient.h"

byte IrcClient::Connect(string host, string port, string pass, string nick, string user, string realname)
{
	OnConnecting();

	if (_ircSocket.Connect(host, port) == 0)
	{
		if (Send("PASS :" + pass) == 0)
		{
			if (Send("NICK :" + nick) == 0)
			{
				if (Send("USER " + user + " 0 * :" + realname) == 0)
				{
					_isConnected = true;
					OnConnected();

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
	OnDisconnecting();

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

	OnDisconnected();
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

byte IrcClient::Send(string data)
{
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
	ircMessage.time = system_clock::to_time_t(system_clock::now());

	size_t currentPosStart{};
	size_t currentPosEnd{};

	// If the message has a prefix
	if (message.starts_with(':'))
	{

		// Get prefix
		currentPosEnd = message.find(' ', currentPosStart);
		ircMessage.prefix = message.substr(1, currentPosEnd - 1);
		currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);
	}

	// Get command
	currentPosEnd = message.find(' ', currentPosStart);
	ircMessage.command = message.substr(currentPosStart, currentPosEnd - currentPosStart);
	currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1);

	// Get parameter(s)
	for (; currentPosStart != message.size() && currentPosEnd != string::npos; currentPosStart = message.find_first_not_of(' ', currentPosEnd + 1))
	{
		if (message.at(currentPosStart) != ':')
		{
			currentPosEnd = message.find(' ', currentPosStart);
			ircMessage.parameters.push_back(message.substr(currentPosStart, currentPosEnd - currentPosStart));
		}

		else
		{
			++currentPosStart;
			ircMessage.parameters.push_back(message.substr(currentPosStart));
			break;
		}
	}

	_messages.push_back(ircMessage);

	if (ircMessage.command == "PRIVMSG" || ircMessage.command == "JOIN" || ircMessage.command == "PART" || ircMessage.command == "MODE")
	{
		bool channelAlreadyExists = false;

		for (size_t i{}; i < _channel.size(); ++i)
		{
			if (_channel.at(i).channelName == ircMessage.parameters.front())
			{
				channelAlreadyExists = true;
				_channel.at(i).messages.push_back(ircMessage);
				break;
			}
		}

		if (!channelAlreadyExists)
		{
			_channel.push_back(IrcChannel{ ircMessage.parameters.front() });

			OnNewChannel(ircMessage.parameters.front());

			_channel.back().messages.push_back(ircMessage);
		}

		OnChannelEvent(ircMessage);
	}

	return 0;
}

byte IrcClient::Process(IrcMessage ircMessage)
{
	if (ircMessage.command == "PRIVMSG")
	{
		OnPrivmsg(ircMessage);
	}

	else if (ircMessage.command == "PING")
	{
		return Send("PONG :" + ircMessage.parameters.front());
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
