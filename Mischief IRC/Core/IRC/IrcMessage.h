#pragma once

#include <chrono>
#include <string>
#include <vector>

using std::time_t;
using std::string;
using std::vector;

struct IrcMessage
{
	time_t time{};
	string prefix{};
	string command{};
	vector<string> parameters{};
};
