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

		_isConnected = false;
		return _ircSocket.Disconnect();
	}

	else
	{
		return _ircSocket.Disconnect();
	}
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

			Process(message);
		}
	}

	return 0;
}

byte IrcClient::Process(string message)
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
		currentPosStart = currentPosEnd + 1;
	}

	// Get command
	currentPosEnd = message.find(' ', currentPosStart);
	ircMessage.command = message.substr(currentPosStart, currentPosEnd - currentPosStart);
	currentPosStart = currentPosEnd + 1;

	// Get parameter(s)
	for (; currentPosStart != message.size() && currentPosEnd != string::npos; currentPosStart = currentPosEnd + 1)
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

	if (ircMessage.command == "PING")
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
