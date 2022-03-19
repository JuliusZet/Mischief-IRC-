#include "pch.h"
#include "IrcClient.h"

byte IrcClient::Connect(std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname)
{
	if (_ircSocket.Connect(host, port) == 0)
	{
		if (Send("PASS " + pass) == 0)
		{
			if (Send("NICK " + nick) == 0)
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

byte IrcClient::Disconnect(std::string quitMessage)
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

byte IrcClient::Send(std::string data)
{
	return _ircSocket.SendData(data + '\n');
}

byte IrcClient::Receive()
{
	std::string buffer = _ircSocket.ReceiveData();

	std::string line{};
	std::istringstream iStringStream{ buffer };

	while (getline(iStringStream, line))
	{
		if (line.back() == '\r')
		{
			line.pop_back();
		}
	}

	return Parse(line);
}

byte IrcClient::Parse(std::string line)
{
	std::string command = line.substr(0, line.find_first_of(' '));

	std::vector<std::string> parameters{};

	for (size_t currentPosStart = command.size() + 1, currentPosEnd{}; currentPosEnd != std::string::npos; currentPosStart = currentPosEnd + 1)
	{
		currentPosEnd = line.find(' ', currentPosStart);
		parameters.push_back(line.substr(currentPosStart, currentPosEnd - currentPosStart));
	}

	return 0;
}
