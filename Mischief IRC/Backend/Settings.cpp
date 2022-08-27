#include "pch.h"
#include "Backend/Settings.h"

std::vector<Setting> Settings::_settings{};

std::string Settings::Get(std::string key)
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

std::string Settings::GetDefault(std::string key)
{
	// ToDo: Add default values
	return "";
}

byte Settings::Set(std::string key, std::string value)
{
	
	// Check if the setting already exists
	for (size_t i{}; i != _settings.size(); ++i)
	{

		// If the setting already exists, overwrite its value
		if (_settings.at(i).key == key)
		{
			_settings.at(i).previousValue = _settings.at(i).value;
			_settings.at(i).value = value;
			_settings.at(i).modified = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			return 0;
		}
	}

	// If the setting does not exist yet, add it
	_settings.push_back(Setting(key, value));

	return 0;
}

byte Settings::SetToDefault(std::string key)
{
	return Set(key, GetDefault(key));
}
