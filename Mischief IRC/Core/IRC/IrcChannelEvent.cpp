#include "pch.h"
#include "IrcChannelEvent.h"

size_t IrcChannelEvent::AddFunction(function<void(IrcChannel)> function)
{
	_functions.push_back(make_pair(_nextFunctionId, function));
	return _nextFunctionId++;
}

void IrcChannelEvent::RemoveFunction(size_t functionId)
{
	for (size_t i{}; i != _functions.size(); ++i)
	{
		if (_functions.at(i).first == functionId)
		{
			_functions.erase(_functions.begin() + i);
			return;
		}
	}
}

void IrcChannelEvent::ClearFunctions()
{
	_functions.clear();
}

void IrcChannelEvent::InvokeFunctions(IrcChannel ircChannel)
{
	for (pair<size_t, function<void(IrcChannel)>>& eachFunction : _functions)
	{
		eachFunction.second(ircChannel);
	}
}
