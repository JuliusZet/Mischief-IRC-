#pragma once

#include "AppearanceSettingsPage.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage>
    {
    private:

    public:
        AppearanceSettingsPage();
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage, implementation::AppearanceSettingsPage>
    {
    };
}
