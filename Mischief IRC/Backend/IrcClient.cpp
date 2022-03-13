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
	Send("QUIT :" + quitMessage);
	return _ircSocket.Disconnect();
}

byte IrcClient::Disconnect()
{
	Send("QUIT");
	return _ircSocket.Disconnect();
}

byte IrcClient::Send(std::string data)
{
	return _ircSocket.SendData(data + '\n');
}
