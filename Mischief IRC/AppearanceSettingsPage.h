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
        void TextBoxTimestampFormat_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TextBoxTimestampFormat_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void TextBoxTimestampFormat_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        size_t _theme{};
        size_t _timestampFormat{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage, implementation::AppearanceSettingsPage>
    {
    };
}
