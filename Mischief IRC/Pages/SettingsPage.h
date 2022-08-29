#pragma once

#include "SettingsPage.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
