#include "pch.h"
#include "IrcPage.h"
#if __has_include("IrcPage.g.cpp")
#include "IrcPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::IrcPage::IrcPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

        // Find out which channel this page is displaying
        winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem selectedItem = MainPage::Current->NavigationView().SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();
        if (selectedItem)
        {
            _channelName = to_string(unbox_value_or<hstring>(selectedItem.Tag(), L""));
        }
    }

    void winrt::Mischief_IRC::implementation::IrcPage::AddIrcMessage(IrcMessage ircMessage)
    {
        if (Grid().IsLoaded())
        {
            Grid().RowDefinitions().Append(winrt::Windows::UI::Xaml::Controls::RowDefinition());
            Grid().RowDefinitions().GetAt(Grid().RowDefinitions().Size() - 1).Height(winrt::Windows::UI::Xaml::GridLength(0, winrt::Windows::UI::Xaml::GridUnitType::Auto));

            winrt::Windows::UI::Xaml::Controls::TextBlock time;
            time.Text(to_hstring(ircMessage.time));
            winrt::Windows::UI::Xaml::Controls::TextBlock sender;
            sender.Text(to_hstring(ircMessage.prefix.substr(0, ircMessage.prefix.find_first_of('!'))));
            sender.HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);
            winrt::Windows::UI::Xaml::Controls::TextBlock message;

            if (ircMessage.command == "PRIVMSG")
            {
                message.Text(to_hstring(ircMessage.parameters.at(1)));
            }
            else
            {
                message.Text(to_hstring(ircMessage.command + ' ' + ircMessage.parameters.front()));
            }

            Grid().Children().Append(time);
            Grid().SetColumn(time, 0);
            Grid().SetRow(time, Grid().RowDefinitions().Size() - 1);
            Grid().Children().Append(sender);
            Grid().SetColumn(sender, 2);
            Grid().SetRow(sender, Grid().RowDefinitions().Size() - 1);
            Grid().Children().Append(message);
            Grid().SetColumn(message, 4);
            Grid().SetRow(message, Grid().RowDefinitions().Size() - 1);
        }
    }

    void winrt::Mischief_IRC::implementation::IrcPage::Grid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        // If the channel exists, then load all messages
        for (IrcChannel eachChannel : MainPage::Current->IrcClient.Channels)
        {
            if (eachChannel.channelName == _channelName)
            {
                for (IrcMessage eachMessage : eachChannel.messages)
                {
                    AddIrcMessage(eachMessage);
                }
                return;
            }
        }
    }
}
