#pragma once

#include <chrono>
#include <string>
#include "winrt/Windows.Storage.h"

using std::chrono::system_clock;
using std::string;
using winrt::box_value;
using winrt::hstring;
using winrt::to_hstring;
using winrt::to_string;
using winrt::unbox_value;

class Settings
{
public:
	static string Get(string key);
	static string GetDefault(string key);
	static byte Set(string key, string value);
	static byte SetToDefault(string key);

private:
	Settings() {};
	static winrt::Windows::Storage::ApplicationDataContainer _localSettings;
};
