#pragma once

#include "Backend/Setting.h"
#include <vector>

class Settings
{
public:
	static std::string Get(std::string key);
	static std::string GetDefault(std::string key);
	static byte Set(std::string key, std::string value);
	static byte SetToDefault(std::string key);

private:
	static std::vector<Setting> _settings;
	Settings() {};
};
