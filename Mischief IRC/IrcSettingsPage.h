#pragma once

#include "IrcSettingsPage.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct IrcSettingsPage : IrcSettingsPageT<IrcSettingsPage>
    {
    private:

    public:
        IrcSettingsPage();
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct IrcSettingsPage : IrcSettingsPageT<IrcSettingsPage, implementation::IrcSettingsPage>
    {
    };
}
