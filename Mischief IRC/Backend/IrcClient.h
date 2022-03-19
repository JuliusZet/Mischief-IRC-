#pragma once

#include "Backend/IrcSocket.h"
#include <sstream>

class IrcClient
{
public:
	byte Connect(std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname);
	byte Disconnect(std::string quitMessage);
	byte Disconnect();
	byte Send(std::string data);
	byte Receive();
	byte Parse(std::string line);
	bool IsConnected()
	{
		return _isConnected;
	}

private:
	IrcSocket _ircSocket{};
	bool _isConnected{};
};

struct IrcMessage
{
};
