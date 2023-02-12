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

            for (size_t i{}; i != MainPage::Current->IrcClient.Channels.size(); ++i)
            {
                if (MainPage::Current->IrcClient.Channels.at(i).Name == _channelName)
                {
                    _channelIndex = i;
                    _channelExists = true;

                    break;
                }
            }
        }

        _timestampFormat = Settings::Get("appearanceTimestampFormat");
        _timeZone = Settings::Get("appearanceTimeZone");
    }

    void winrt::Mischief_IRC::implementation::IrcPage::Grid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        // If the channel exists, then load all messages
        if (_channelExists)
        {
            for (IrcMessage& eachMessage : MainPage::Current->IrcClient.Channels.at(_channelIndex).Messages)
            {
                AddIrcMessage(eachMessage);
            }

            _eventFunctionId = MainPage::Current->IrcClient.Channels.at(_channelIndex).OnNewMessage.AddFunction(bind(&winrt::Mischief_IRC::implementation::IrcPage::AddIrcMessage, this, _1));

            return;
        }
    }

    void winrt::Mischief_IRC::implementation::IrcPage::AddIrcMessage(IrcMessage ircMessage)
    {
        Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, [this, ircMessage]
            {
                if (Grid().IsLoaded())
                {
                    Grid().RowDefinitions().Append(winrt::Windows::UI::Xaml::Controls::RowDefinition());
                    Grid().RowDefinitions().GetAt(Grid().RowDefinitions().Size() - 1).Height(winrt::Windows::UI::Xaml::GridLengthHelper::Auto());

                    winrt::Windows::UI::Xaml::Controls::TextBlock time;
                    winrt::Windows::UI::Xaml::Controls::TextBlock sender;
                    winrt::Windows::UI::Xaml::Controls::TextBlock message;

                    zoned_time zonedTime{ _timeZone, floor<seconds>(ircMessage.Time) };
                    time.Text(to_hstring(vformat(_timestampFormat, make_format_args(zonedTime))));
                    
                    sender.HorizontalAlignment(winrt::Windows::UI::Xaml::HorizontalAlignment::Right);

                    if (ircMessage.Command == "PRIVMSG")
                    {
                        if (ircMessage.Parameters.at(1).starts_with("ACTION ") && ircMessage.Parameters.at(1).ends_with(''))
                        {
                            sender.Text(L"*");
                            message.Text(to_hstring(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')) + ' ' + ircMessage.Parameters.at(1).substr(8, ircMessage.Parameters.at(1).size() - 9)));
                        }

                        else
                        {
                            sender.Text(to_hstring(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!'))));
                            message.Text(to_hstring(ircMessage.Parameters.at(1)));
                        }
                    }

                    else if (ircMessage.Command == "JOIN")
                    {
                        sender.Text(L"*");
                        message.Text(to_hstring(ircMessage.Prefix + " has joined"));
                    }

                    else if (ircMessage.Command == "PART")
                    {
                        sender.Text(L"*");
                        if (ircMessage.Parameters.size() > 1)
                        {
                            message.Text(to_hstring(ircMessage.Prefix + " has left (" + ircMessage.Parameters.at(1) + ')'));
                        }
                        else
                        {
                            message.Text(to_hstring(ircMessage.Prefix + " has left"));
                        }
                    }

                    else if (ircMessage.Command == "MODE")
                    {
                        // Channel Mode
                        if (ircMessage.Parameters.front().starts_with('#'))
                        {
                            sender.Text(L"*");
                            message.Text(to_hstring(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')) + " gives " + ircMessage.Parameters.at(1) + " to " + ircMessage.Parameters.at(2)));
                        }

                        // User Mode
                        else
                        {
                            sender.Text(L"*");
                            message.Text(to_hstring(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!')) + " gives " + ircMessage.Parameters.at(1) + " to " + ircMessage.Parameters.at(0)));
                        }
                    }

                    else if (ircMessage.Command == "QUIT")
                    {
                        sender.Text(L"*");
                        if (ircMessage.Parameters.size() > 0)
                        {
                            message.Text(to_hstring(ircMessage.Prefix + " has quit (" + ircMessage.Parameters.front() + ')'));
                        }
                        else
                        {
                            message.Text(to_hstring(ircMessage.Prefix + " has quit"));
                        }
                    }

                    else
                    {
                        if (ircMessage.Prefix.find('!') == string::npos)
                        {
                            sender.Text(L"*");
                        }
                        else
                        {
                            sender.Text(to_hstring(ircMessage.Prefix.substr(0, ircMessage.Prefix.find_first_of('!'))));
                        }

                        message.Text(to_hstring(ircMessage.Command));

                        for (string parameter : ircMessage.Parameters)
                        {
                            message.Text(message.Text() + ' ' + to_hstring(parameter));
                        }
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

                    ScrollViewer().UpdateLayout();
                    ScrollViewer().ScrollToVerticalOffset(ScrollViewer().ScrollableHeight());
                }
            }
        );
    }

    void winrt::Mischief_IRC::implementation::IrcPage::Page_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        if (_channelExists)
        {
            MainPage::Current->IrcClient.Channels.at(_channelIndex).OnNewMessage.RemoveFunction(_eventFunctionId);
        }
    }

    void winrt::Mischief_IRC::implementation::IrcPage::TextBoxMessage_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
    {
        if (e.Key() == winrt::Windows::System::VirtualKey::Enter)
        {
            MainPage::Current->IrcClient.SendPrivmsg(_channelName, to_string(TextBoxMessage().Text()));
            TextBoxMessage().Text(L"");
        }
    }

    void winrt::Mischief_IRC::implementation::IrcPage::ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        MainPage::Current->IrcClient.SendPrivmsg(_channelName, to_string(TextBoxMessage().Text()));
        TextBoxMessage().Text(L"");
    }
}
