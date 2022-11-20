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

struct IrcMessage
{
	time_point<system_clock> Time{};
	string Prefix{};
	string Command{};
	vector<string> Parameters{};
};
