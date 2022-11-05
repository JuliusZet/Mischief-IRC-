#pragma once

#include "IrcPage.g.h"
#include "MainPage.h"

using std::bind;
using namespace std::placeholders;

namespace winrt::Mischief_IRC::implementation
{
    struct IrcPage : IrcPageT<IrcPage>
    {
    public:
        IrcPage();
        void Grid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AddIrcMessage(IrcMessage ircMessage);
        void Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        string _channelName{};
        size_t _channelIndex{};
        bool _channelExists{};
        size_t _eventFunctionId{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct IrcPage : IrcPageT<IrcPage, implementation::IrcPage>
    {
    };
}
