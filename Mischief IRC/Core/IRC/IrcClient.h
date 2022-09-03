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
	byte SendPrivmsg(string receiver, string text);
	bool IsConnected();

private:
	byte Send(string data);
	byte Receive();
	thread ReceiveAsync();
	byte Process(string message);

	IrcSocket _ircSocket{};
	vector<IrcMessage> _messages{};
	thread _receiveThread{};
	bool _isConnected{};
};
