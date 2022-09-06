#pragma once

#include <vector>
#include "Core/Settings/Settings.h"
#include "SettingsPage.g.h"
#include "winrt/Windows.UI.Text.h"

using std::make_pair;
using std::pair;
using std::vector;
using std::wstring;

namespace winrt::Mischief_IRC::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
    private:
        vector<pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>> _pages;
    public:
        SettingsPage();
        static winrt::Mischief_IRC::implementation::SettingsPage* Current;
        void NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
        void NavigationView_Navigate(wstring navItemTag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo);
        void On_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);
        void FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e);
        void ButtonDiscard_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ButtonSave_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        pair<hstring, hstring> IrcHost{ to_hstring(Settings::Get("ircHost")), to_hstring(Settings::Get("ircHost")) };
        pair<hstring, hstring> IrcPort{ to_hstring(Settings::Get("ircPort")), to_hstring(Settings::Get("ircPort")) };
        pair<hstring, hstring> IrcPass{ to_hstring(Settings::Get("ircPass")), to_hstring(Settings::Get("ircPass")) };
        pair<hstring, hstring> IrcNick{ to_hstring(Settings::Get("ircNick")), to_hstring(Settings::Get("ircNick")) };
        pair<hstring, hstring> IrcUser{ to_hstring(Settings::Get("ircUser")), to_hstring(Settings::Get("ircUser")) };
        pair<hstring, hstring> IrcRealname{ to_hstring(Settings::Get("ircRealname")), to_hstring(Settings::Get("ircRealname")) };
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
