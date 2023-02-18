#pragma once

#include "Core/IRC/IrcMessage.h"
#include "Core/IRC/IrcMessageEvent.h"
#include "Core/IRC/IrcChannelUser.h"

class IrcChannel
{
public:
	IrcChannel(){}
	IrcChannel(string name);
	void AddMessage(IrcMessage ircMessage);

	IrcMessageEvent OnNewMessage;

	string Name{};
	string Topic{};
	vector<IrcMessage> Messages{};
	vector<IrcChannelUser> Users{};
};
