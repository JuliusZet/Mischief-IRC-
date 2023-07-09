#pragma once

#include "CalloutCreatorPage.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct CalloutCreatorPage : CalloutCreatorPageT<CalloutCreatorPage>
    {
    private:

    public:
        CalloutCreatorPage();
        void TextBoxMessage_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e);
        void ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CheckBoxCasenumber_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CheckBoxCasenumber_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void TextBoxCasenumber_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct CalloutCreatorPage : CalloutCreatorPageT<CalloutCreatorPage, implementation::CalloutCreatorPage>
    {
    };
}
