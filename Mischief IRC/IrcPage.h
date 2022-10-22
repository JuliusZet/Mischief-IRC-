﻿#pragma once

#include "IrcPage.g.h"
#include "MainPage.h"

namespace winrt::Mischief_IRC::implementation
{
    struct IrcPage : IrcPageT<IrcPage>
    {
    public:
        IrcPage();
        void Grid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AddIrcMessage(IrcMessage ircMessage);

    private:
        string _channelName{};
        size_t _channelIndex{};
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct IrcPage : IrcPageT<IrcPage, implementation::IrcPage>
    {
    };
}
