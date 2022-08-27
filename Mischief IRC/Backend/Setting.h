#pragma once

#include <chrono>
#include <string>

struct Setting
{
	std::string key{};
	std::string value{};
	std::string previousValue{};
	std::time_t created{};
	std::time_t modified{};
	Setting(std::string key, std::string value)
		: key{ key }
		, value{ value }
		, created{ std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) }
		, modified{ created }
	{};
};
