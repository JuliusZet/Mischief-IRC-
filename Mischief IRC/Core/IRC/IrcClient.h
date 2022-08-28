#pragma once

#include <sstream>
#include <thread>
#include "Core/IRC/IrcMessage.h"
#include "Core/IRC/IrcSocket.h"

using std::chrono::system_clock;
using std::istringstream;
using std::string;
using std::thread;
using std::vector;

class IrcClient
{
public:
	byte Connect(string host, string port, string pass, string nick, string user, string realname);
	byte Disconnect(string quitMessage);
	byte Disconnect();
	byte Reconnect(string quitMessage, string host, string port, string pass, string nick, string user, string realname);
	byte Reconnect(string host, string port, string pass, string nick, string user, string realname);
	byte Send(string data);
	byte SendPrivmsg(string receiver, string text);
	byte Receive();
	byte Process(string message);
	thread ReceiveAsync();
	bool IsConnected();

private:
	IrcSocket _ircSocket{};
	bool _isConnected{};
	vector<IrcMessage> _messages{};
};
