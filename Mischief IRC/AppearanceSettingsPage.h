#pragma once

#include "AppearanceSettingsPage.g.h"
#include "Core/Settings/Settings.h"
#include "SettingsPage.h"

namespace winrt::Mischief_IRC::implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage>
    {
    public:
        AppearanceSettingsPage();
        void RadioButtonsTheme_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void RadioButtonsTheme_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

    private:
        size_t _theme{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage, implementation::AppearanceSettingsPage>
    {
    };
}
