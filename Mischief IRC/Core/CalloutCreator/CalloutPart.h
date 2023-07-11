#pragma once

#include <string>

using std::string;

class CalloutPart
{
public:
	CalloutPart() {};
	CalloutPart(string name, string text)
	{
		Name = name;
		Text = text;
	}
	string Name{};
	string Text{};
};
