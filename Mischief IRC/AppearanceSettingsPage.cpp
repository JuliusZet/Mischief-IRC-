#include "pch.h"
#include "AppearanceSettingsPage.h"
#if __has_include("AppearanceSettingsPage.g.cpp")
#include "AppearanceSettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::AppearanceSettingsPage::AppearanceSettingsPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }
}
