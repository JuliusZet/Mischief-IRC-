#pragma once

#include <functional>
#include "Core/IRC/IrcMessage.h"

using std::bind;
using std::function;
using std::make_pair;
using std::pair;
using namespace std::placeholders;

class IrcMessageEvent
{
public:
	size_t AddFunction(function<void(IrcMessage)> function);
	void RemoveFunction(size_t functionId);
	void ClearFunctions();
	void InvokeFunctions(IrcMessage ircMessage);

private:
	vector<std::pair<size_t, function<void(IrcMessage)>>> _functions{};
	size_t _nextFunctionId{};
};
