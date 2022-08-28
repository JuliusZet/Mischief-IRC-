#pragma once

#include <vector>
#include "Core/Settings/Setting.h"

using std::string;
using std::vector;

class Settings
{
public:
	static string Get(string key);
	static string GetDefault(string key);
	static byte Set(string key, string value);
	static byte SetToDefault(string key);

private:
	static vector<Setting> _settings;
	Settings() {};
};
