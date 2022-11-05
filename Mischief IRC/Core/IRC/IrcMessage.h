#pragma once

#include <chrono>
#include <string>
#include <vector>

using std::chrono::system_clock;
using std::put_time;
using std::time_t;
using std::tm;
using std::string;
using std::vector;

struct IrcMessage
{
	time_t Time{};
	string Prefix{};
	string Command{};
	vector<string> Parameters{};
};
