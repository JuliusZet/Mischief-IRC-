#pragma once

#include "AppearanceSettingsPage.g.h"
#include "Core/Settings/Settings.h"
#include "SettingsPage.h"
#include "TimestampFormatHelpDialog.h"

using winrt::single_threaded_vector;
using winrt::Windows::Foundation::Collections::IVector;

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
        void ButtonTimestampFormatHelp_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ButtonTimestampFormatReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AutoSuggestBoxTimeZone_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AutoSuggestBoxTimeZone_TextChanged(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);
        void AutoSuggestBoxTimeZone_SuggestionChosen(winrt::Windows::UI::Xaml::Controls::AutoSuggestBox const& sender, winrt::Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs const& args);
        void AutoSuggestBoxTimeZone_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ButtonTimeZoneReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        size_t _theme{};
        size_t _timestampFormat{};
        size_t _timeZone{};
        IVector<IInspectable> _timeZones{};
        const tzdb& _tzdb = get_tzdb();
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct AppearanceSettingsPage : AppearanceSettingsPageT<AppearanceSettingsPage, implementation::AppearanceSettingsPage>
    {
    };
}
