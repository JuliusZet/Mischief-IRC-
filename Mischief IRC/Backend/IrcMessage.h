#pragma once

#include <chrono>
#include <string>
#include <vector>

struct IrcMessage
{
	std::time_t time{};
	std::string prefix{};
	std::string command{};
	std::vector<std::string> parameters{};
};