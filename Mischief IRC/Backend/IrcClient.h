#pragma once

#include "Backend/IrcSocket.h"
#include <sstream>

class IrcClient
{
public:
	byte Connect(std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname);
	byte Disconnect(std::string quitMessage);
	byte Disconnect();
	byte Reconnect(std::string quitMessage, std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname);
	byte Reconnect(std::string host, std::string port, std::string pass, std::string nick, std::string user, std::string realname);
	byte Send(std::string data);
	byte SendPrivmsg(std::string receiver, std::string text);
	byte Receive();
	byte Process(std::string message);
	Windows::Foundation::IAsyncAction^ ReceiveAsync();
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
