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

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxPort_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxPort_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::PasswordBoxPass_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::PasswordBoxPass_PasswordChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::PasswordBoxPass_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxNick_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxUser_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {

    }

    void winrt::Mischief_IRC::implementation::IrcSettingsPage::TextBoxRealname_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {

    }
}
