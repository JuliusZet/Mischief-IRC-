#pragma once

#include "MainPage.g.h"
#include "Core/IRC/IrcClient.h"
#include "Core/Settings/Settings.h"

using winrt::box_value;
using winrt::Windows::Foundation::IInspectable;
using winrt::Windows::UI::Xaml::Controls::ContentDialog;
using winrt::Windows::UI::Xaml::RoutedEventArgs;

namespace winrt::Mischief_IRC::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        IrcClient ircClient;

        void OnIrcClientConnectionStatusChanged();
        void MenuFlyoutItemMischiefIrcSettings_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void MenuFlyoutItemMischiefIrcExit_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void MenuFlyoutItemIrcClientConnect_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void MenuFlyoutItemIrcClientReconnect_Click(IInspectable const& sender, RoutedEventArgs const& e);
        void MenuFlyoutItemIrcClientDisconnect_Click(IInspectable const& sender, RoutedEventArgs const& e);
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
