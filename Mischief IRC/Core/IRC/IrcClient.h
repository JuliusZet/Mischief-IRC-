#pragma once

#include <sstream>
#include <thread>
#include "Core/IRC/IrcChannel.h"
#include "Core/IRC/IrcSocket.h"

using std::istringstream;
using std::stringstream;
using std::thread;

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

	vector<IrcChannel> Channels{};

private:
	byte Send(string data);
	byte Receive();
	thread ReceiveAsync();
	byte Parse(string message);
	byte Process(IrcMessage ircMessage);

	IrcSocket _ircSocket{};
	vector<IrcMessage> _messages{};
	thread _receiveThread{};
	bool _isConnected{};
};
