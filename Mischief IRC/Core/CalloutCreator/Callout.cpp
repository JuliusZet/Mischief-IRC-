#include "pch.h"
#include "Core/CalloutCreator/Callout.h"

vector<CalloutPart> Callout::_callout;

byte Callout::Prepend(string calloutPartName, string calloutPartText)
{
	_callout.insert(_callout.begin(), CalloutPart(calloutPartName, calloutPartText));
	return 0;
}

byte Callout::Prepend(string calloutPartName)
{
	return Callout::Prepend(calloutPartName, "");
}

byte Callout::Append(string calloutPartName, string calloutPartText)
{
	_callout.push_back(CalloutPart(calloutPartName, calloutPartText));
	return 0;
}

byte Callout::Append(string calloutPartName)
{
	return Callout::Append(calloutPartName, "");
}

byte Callout::Replace(string calloutPartName, string calloutPartText)
{
	for (CalloutPart& eachCalloutPart : _callout)
	{
		if (eachCalloutPart.Name == calloutPartName)
		{
			eachCalloutPart.Text = calloutPartText;
			return 0;
		}
	}

	return 1;
}

byte Callout::Remove(string calloutPartName)
{
	for (size_t i{}; i < _callout.size(); ++i)
	{
		if (_callout.at(i).Name == calloutPartName)
		{
			_callout.erase(_callout.begin() + i);
			return 0;
		}
	}

	return 1;
}

byte Callout::Clear()
{
	_callout.clear();
	return 0;
}

string Callout::Generate()
{
	string callout{};

	for (CalloutPart& eachCalloutPart : _callout)
	{
		callout += eachCalloutPart.Text + ' ';
	}

	// Remove the last space character
	if (!callout.empty())
	{
		callout.pop_back();
	}

	return callout;
}
