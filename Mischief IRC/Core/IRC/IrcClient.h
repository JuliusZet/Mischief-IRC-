#pragma once

#include <sstream>
#include <thread>
#include "Core/IRC/IrcChannelEvent.h"
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
	void AddChannel(IrcChannel ircChannel);
	byte SendPrivmsg(string receiver, string text);
	bool IsConnected();

	IrcChannelEvent OnNewChannel;

	vector<IrcChannel> Channels{};

private:
	byte Send(string data);
	byte Receive();
	thread ReceiveAsync();
	IrcMessage Parse(string message);
	byte Process(IrcMessage ircMessage);
	byte AddMessageToChannel(IrcMessage ircMessage, string channelName);
	byte SetTopicOfChannel(string topic, string channelName);
	byte AddUsersToChannel(string users, string channelName);
	byte RemoveUserFromChannel(string user, string channelName);

	IrcSocket _ircSocket{};
	thread _receiveThread{};
	bool _isConnected{};
	string _nick{};
};
