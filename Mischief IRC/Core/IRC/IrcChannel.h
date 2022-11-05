#pragma once

#include "Core/IRC/IrcMessage.h"
#include "Core/IRC/IrcMessageEvent.h"

class IrcChannel
{
public:
	IrcChannel(){}
	IrcChannel(string name);
	void AddMessage(IrcMessage ircMessage);

	IrcMessageEvent OnChannelEvent;

	string Name{};
	vector<IrcMessage> Messages{};
};
