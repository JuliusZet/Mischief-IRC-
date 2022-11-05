#include "pch.h"
#include "IrcMessageEvent.h"

size_t IrcMessageEvent::AddFunction(function<void(IrcMessage)> function)
{
	_functions.push_back(make_pair(_nextFunctionId, function));
	return _nextFunctionId++;
}

void IrcMessageEvent::RemoveFunction(size_t functionId)
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

void IrcMessageEvent::ClearFunctions()
{
	_functions.clear();
}

void IrcMessageEvent::InvokeFunctions(IrcMessage ircMessage)
{
	for (pair<size_t, function<void(IrcMessage)>>& eachFunction : _functions)
	{
		eachFunction.second(ircMessage);
	}
}
