#pragma once

#include "CalloutCreatorSettingsPage.g.h"
#include "Core/Settings/Settings.h"
#include "SettingsPage.h"

namespace winrt::Mischief_IRC::implementation
{
    struct CalloutCreatorSettingsPage : CalloutCreatorSettingsPageT<CalloutCreatorSettingsPage>
    {
    public:
        CalloutCreatorSettingsPage();
        void TextBoxChannelName_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TextBoxChannelName_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void TextBoxChannelName_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ButtonChannelNameReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        size_t _channelName{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct CalloutCreatorSettingsPage : CalloutCreatorSettingsPageT<CalloutCreatorSettingsPage, implementation::CalloutCreatorSettingsPage>
    {
    };
}
