#pragma once
#include <functional>
#include "Core/IRC/IrcChannel.h"

class IrcChannelEvent
{
public:
	size_t AddFunction(function<void(IrcChannel)> function);
	void RemoveFunction(size_t functionId);
	void ClearFunctions();
	void InvokeFunctions(IrcChannel ircChannel);

private:
	vector<std::pair<size_t, function<void(IrcChannel)>>> _functions{};
	size_t _nextFunctionId{};
};
