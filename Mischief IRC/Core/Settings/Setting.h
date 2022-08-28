#pragma once

#include <chrono>
#include <string>

using std::chrono::system_clock;
using std::string;
using std::time_t;

struct Setting
{
	string key{};
	string value{};
	string previousValue{};
	time_t created{};
	time_t modified{};
	Setting(string key, string value)
		: key{ key }
		, value{ value }
		, created{ system_clock::to_time_t(system_clock::now()) }
		, modified{ created }
	{};
};
