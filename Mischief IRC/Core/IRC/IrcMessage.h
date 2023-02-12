#pragma once

#include <chrono>
#include <string>
#include <vector>

using std::chrono::floor;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::zoned_time;
using std::string;
using std::vector;

class IrcMessage
{
public:
	IrcMessage() {}
	IrcMessage(string prefix, string command, vector<string> parameters)
	{
		Time = system_clock::now();
		Prefix = prefix;
		Command = command;
		Parameters = parameters;
	}

	time_point<system_clock> Time{};
	string Prefix{};
	string Command{};
	vector<string> Parameters{};
};
