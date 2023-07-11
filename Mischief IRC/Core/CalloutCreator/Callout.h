#pragma once

#include <string>
#include <vector>
#include "Core/CalloutCreator/CalloutPart.h"

using std::string;
using std::vector;

class Callout
{
public:
	static byte Prepend(string calloutPartName, string calloutPartText);
	static byte Prepend(string calloutPartName);
	static byte Append(string calloutPartName, string calloutPartText);
	static byte Append(string calloutPartName);
	static byte Replace(string calloutPartName, string calloutPartText);
	static byte Remove(string calloutPartName);
	static byte Clear();
	static string Generate();

private:
	Callout() {};
	static vector<CalloutPart> _callout;
};
