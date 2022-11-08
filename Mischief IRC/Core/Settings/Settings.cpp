#include "pch.h"
#include "Core/Settings/Settings.h"

winrt::Windows::Storage::ApplicationDataContainer Settings::_localSettings{ winrt::Windows::Storage::ApplicationData::Current().LocalSettings() };

string Settings::Get(string key)
{
	hstring hKey{ to_hstring(key) };

	// If the setting exists, return its value
	if (_localSettings.Values().HasKey(hKey))
	{
		return to_string(unbox_value<hstring>(_localSettings.Values().Lookup(hKey)));
	}

	// If the setting does not exist, return its default value
	return GetDefault(key);
}

string Settings::GetDefault(string key)
{
	if (key == "appearanceTheme")
	{
		return "System";
	}
	if (key == "appearanceTimestampFormat")
	{
		return "%T";
	}
	else
	{
		return "";
	}
}

byte Settings::Set(string key, string value)
{
	hstring hKey{ to_hstring(key) };
	hstring hValue{ to_hstring(value) };

	// If the setting already exists, overwrite its value
	if (_localSettings.Values().HasKey(hKey))
	{
		_localSettings.Values().Insert(hKey + L"_previous", _localSettings.Values().Lookup(hKey));
		_localSettings.Values().Insert(hKey, box_value(hValue));
		_localSettings.Values().Insert(hKey + L"_modified", box_value(system_clock::to_time_t(system_clock::now())));
		return 0;
	}

	// If the setting does not exist yet, add it
	_localSettings.Values().Insert(hKey, box_value(hValue));
	_localSettings.Values().Insert(hKey + L"_created", box_value(system_clock::to_time_t(system_clock::now())));
	_localSettings.Values().Insert(hKey + L"_modified", _localSettings.Values().Lookup(hKey + L"created"));

	return 0;
}

byte Settings::SetToDefault(string key)
{
	return Set(key, GetDefault(key));
}
