#pragma once

#include "MainPage.g.h"
#include "Core/IRC/IrcClient.h"
#include "Core/Settings/Settings.h"

using std::make_pair;
using std::pair;
using std::vector;
using std::wstring;

namespace winrt::Mischief_IRC::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
    public:
        MainPage();
        static winrt::Mischief_IRC::implementation::MainPage* Current;
        void NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
        void NavigationView_Navigate(wstring navItemTag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo);
        void On_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& args);
        void FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e);
        void IrcConnect();
        void IrcDisconnect();

        IrcClient IrcClient{};

    private:
        vector<pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>> _pages{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
