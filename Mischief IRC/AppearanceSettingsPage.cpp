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

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::RadioButtonsTheme_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "appearanceTheme")
            {
                _theme = i;
                break;
            }
        }

        if (SettingsPage::Current->settings.at(_theme).newValue == L"Light")
        {
            RadioButtonsTheme().SelectedIndex(0);
        }
        else if (SettingsPage::Current->settings.at(_theme).newValue == L"Dark")
        {
            RadioButtonsTheme().SelectedIndex(1);
        }
        else
        {
            RadioButtonsTheme().SelectedIndex(2);
        }
    }

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::RadioButtonsTheme_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        switch (RadioButtonsTheme().SelectedIndex())
        {
        case 0:
            SettingsPage::Current->settings.at(_theme).newValue = L"Light";
            break;
        case 1:
            SettingsPage::Current->settings.at(_theme).newValue = L"Dark";
            break;
        case 2:
            SettingsPage::Current->settings.at(_theme).newValue = L"System";
            break;
        default:
            break;
        }
    }

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::TextBoxTimestampFormat_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "appearanceTimestampFormat")
            {
                _timestampFormat = i;
                break;
            }
        }

        TextBoxTimestampFormat().Text(SettingsPage::Current->settings.at(_timestampFormat).newValue);
    }

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::TextBoxTimestampFormat_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxTimestampFormat().Text() != SettingsPage::Current->settings.at(_timestampFormat).savedValue)
        {
            TextBoxTimestampFormat().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxTimestampFormat().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::TextBoxTimestampFormat_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_timestampFormat).newValue = TextBoxTimestampFormat().Text();
    }

    void winrt::Mischief_IRC::implementation::AppearanceSettingsPage::ButtonTimestampFormatReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_timestampFormat).newValue = to_hstring(Settings::GetDefault("appearanceTimestampFormat"));
        TextBoxTimestampFormat().Text(SettingsPage::Current->settings.at(_timestampFormat).newValue);
    }
}
