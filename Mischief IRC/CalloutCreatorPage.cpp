#include "pch.h"
#include "CalloutCreatorPage.h"
#if __has_include("CalloutCreatorPage.g.cpp")
#include "CalloutCreatorPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	winrt::Mischief_IRC::implementation::CalloutCreatorPage::CalloutCreatorPage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxMessage_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxCasenumber_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxCasenumber_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxCasenumber_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{

	}
}
