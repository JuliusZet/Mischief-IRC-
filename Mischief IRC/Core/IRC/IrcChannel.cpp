#include "pch.h"
#include "Core/IRC/IrcChannel.h"

IrcChannel::IrcChannel(string name)
{
	Name = name;
}

void IrcChannel::AddMessage(IrcMessage ircMessage)
{
	Messages.push_back(ircMessage);
	OnChannelEvent.InvokeFunctions(ircMessage);
}
