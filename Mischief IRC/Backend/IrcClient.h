#pragma once

#include "Backend/IrcSocket.h"

class IrcClient
{
public:
	byte Connect(std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname);
	byte Disconnect(std::string quitMessage);
	byte Disconnect();
	byte Send(std::string data);

private:
	IrcSocket _ircSocket;
};

struct IrcMessage
{
};
