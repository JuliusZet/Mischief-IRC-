#pragma once

#include "Core/IRC/IrcMessage.h"

struct IrcChannel
{
	void AddMessage(IrcMessage ircMessage)
	{
		Messages.push_back(ircMessage);
	}

	string Name{};
	vector<IrcMessage> Messages{};
};
