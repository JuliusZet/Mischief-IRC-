#include "pch.h"
#include "CalloutCreatorSettingsPage.h"
#if __has_include("CalloutCreatorSettingsPage.g.cpp")
#include "CalloutCreatorSettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::CalloutCreatorSettingsPage::CalloutCreatorSettingsPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    void winrt::Mischief_IRC::implementation::CalloutCreatorSettingsPage::TextBoxChannelName_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "calloutCreatorChannelName")
            {
                _channelName = i;
                break;
            }
        }

        TextBoxChannelName().Text(SettingsPage::Current->settings.at(_channelName).newValue);
    }

    void winrt::Mischief_IRC::implementation::CalloutCreatorSettingsPage::TextBoxChannelName_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxChannelName().Text() != SettingsPage::Current->settings.at(_channelName).savedValue)
        {
            TextBoxChannelName().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxChannelName().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::CalloutCreatorSettingsPage::TextBoxChannelName_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_channelName).newValue = TextBoxChannelName().Text();
    }

    void winrt::Mischief_IRC::implementation::CalloutCreatorSettingsPage::ButtonChannelNameReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_channelName).newValue = to_hstring(Settings::GetDefault("calloutCreatorChannelName"));
        TextBoxChannelName().Text(SettingsPage::Current->settings.at(_channelName).newValue);
    }
}
