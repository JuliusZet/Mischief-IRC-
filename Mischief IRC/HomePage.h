#pragma once

#include "HomePage.g.h"
#include "Core/IRC/IrcClient.h"

namespace winrt::Mischief_IRC::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
    private:
        IrcClient _ircClient;

    public:
        HomePage();
        void ButtonIrcConnect_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
