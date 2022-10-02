#pragma once

#include <vector>
#include "Core/Settings/Settings.h"
#include "MainPage.h"
#include "SettingsPage.g.h"
#include "winrt/Windows.UI.Text.h"
#include "winrt/Windows.Foundation.h"

using std::make_pair;
using std::pair;
using std::vector;
using std::wstring;

namespace winrt::Mischief_IRC::implementation
{
    struct Setting
    {
        string key{};
        hstring savedValue{};
        hstring newValue{};

        Setting(string key) :
            key{ key },
            savedValue{ to_hstring(Settings::Get(key)) },
            newValue{ savedValue }
        { }
    };

    struct SettingsPage : SettingsPageT<SettingsPage>
    {
    public:
        SettingsPage();
        static winrt::Mischief_IRC::implementation::SettingsPage* Current;
        void NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
        void NavigationView_Navigate(wstring navItemTag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo);
        void FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction ButtonSave_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction ButtonDiscard_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        vector<Setting> settings{};

    private:
        vector<pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>> _pages;
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
