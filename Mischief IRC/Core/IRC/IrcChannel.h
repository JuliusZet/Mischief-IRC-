#pragma once

#include "Core/IRC/IrcMessage.h"

struct IrcChannel
{
	string channelName{};
	vector<IrcMessage> messages{};
};
