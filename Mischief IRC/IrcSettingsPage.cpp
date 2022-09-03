#include "pch.h"
#include "IrcSettingsPage.h"
#if __has_include("IrcSettingsPage.g.cpp")
#include "IrcSettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::IrcSettingsPage::IrcSettingsPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }
}
