#include "pch.h"
#include "IrcSettingsPage.h"
#if __has_include("IrcSettingsPage.g.cpp")
#include "IrcSettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::IrcSettingsPage::IrcSettingsPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxHost_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircHost")
            {
                _host = i;
                break;
            }
        }

        TextBoxHost().Text(SettingsPage::Current->settings.at(_host).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxHost_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxHost().Text() != SettingsPage::Current->settings.at(_host).savedValue)
        {
            TextBoxHost().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxHost().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxHost_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_host).newValue = TextBoxHost().Text();
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxPort_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircPort")
            {
                _port = i;
                break;
            }
        }

        TextBoxPort().Text(SettingsPage::Current->settings.at(_port).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxPort_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxPort().Text() != SettingsPage::Current->settings.at(_port).savedValue)
        {
            TextBoxPort().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxPort().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxPort_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_port).newValue = TextBoxPort().Text();
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::PasswordBoxPass_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircPass")
            {
                _pass = i;
                break;
            }
        }

        PasswordBoxPass().Password(SettingsPage::Current->settings.at(_pass).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::PasswordBoxPass_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_pass).newValue = PasswordBoxPass().Password();
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircNick")
            {
                _nick = i;
                break;
            }
        }

        TextBoxNick().Text(SettingsPage::Current->settings.at(_nick).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxNick().Text() != SettingsPage::Current->settings.at(_nick).savedValue)
        {
            TextBoxNick().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxNick().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_nick).newValue = TextBoxNick().Text();
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircUser")
            {
                _user = i;
                break;
            }
        }

        TextBoxUser().Text(SettingsPage::Current->settings.at(_user).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxUser().Text() != SettingsPage::Current->settings.at(_user).savedValue)
        {
            TextBoxUser().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxUser().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_user).newValue = TextBoxUser().Text();
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        for (size_t i{}; i != SettingsPage::Current->settings.size(); ++i)
        {
            if (SettingsPage::Current->settings.at(i).key == "ircRealname")
            {
                _realname = i;
                break;
            }
        }

        TextBoxRealname().Text(SettingsPage::Current->settings.at(_realname).newValue);
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        if (TextBoxRealname().Text() != SettingsPage::Current->settings.at(_realname).savedValue)
        {
            TextBoxRealname().FontWeight(winrt::Windows::UI::Text::FontWeights::Bold());
        }

        else
        {
            TextBoxRealname().FontWeight(winrt::Windows::UI::Text::FontWeights::Normal());
        }
    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        SettingsPage::Current->settings.at(_realname).newValue = TextBoxRealname().Text();
    }
}
