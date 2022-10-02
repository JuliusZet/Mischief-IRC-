#pragma once

#include <boost/signals2.hpp>
#include <sstream>
#include <thread>
#include "Core/IRC/IrcChannel.h"
#include "Core/IRC/IrcSocket.h"

using boost::signals2::signal;
using std::chrono::system_clock;
using std::istringstream;
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

	signal<void()> OnConnecting;
	signal<void()> OnConnected;
	signal<void()> OnDisconnecting;
	signal<void()> OnDisconnected;
	signal<void(string)> OnNewChannel;
	signal<void(IrcMessage)> OnChannelEvent;
	signal<void(IrcMessage)> OnPrivmsg;

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
