#include "pch.h"
#include "Core/Settings/Settings.h"

vector<Setting> Settings::_settings{};

string Settings::Get(string key)
{

	// Check if the setting exists
	for (size_t i{}; i != _settings.size(); ++i)
	{

		// If the setting exists, return its value
		if (_settings.at(i).key == key)
		{
			return _settings.at(i).value;
		}
	}

	// If the setting does not exist, return its default value
	return GetDefault(key);
}

string Settings::GetDefault(string key)
{
	// ToDo: Add default values
	return "";
}

byte Settings::Set(string key, string value)
{

	// Check if the setting already exists
	for (size_t i{}; i != _settings.size(); ++i)
	{

		// If the setting already exists, overwrite its value
		if (_settings.at(i).key == key)
		{
			_settings.at(i).previousValue = _settings.at(i).value;
			_settings.at(i).value = value;
			_settings.at(i).modified = system_clock::to_time_t(system_clock::now());
			return 0;
		}
	}

	// If the setting does not exist yet, add it
	_settings.push_back(Setting(key, value));

	return 0;
}

byte Settings::SetToDefault(string key)
{
	return Set(key, GetDefault(key));
}
