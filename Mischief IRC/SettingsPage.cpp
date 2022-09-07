#include "pch.h"
#include "SettingsPage.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	winrt::Mischief_IRC::implementation::SettingsPage* SettingsPage::Current{ nullptr };

	winrt::Mischief_IRC::implementation::SettingsPage::SettingsPage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

		Current = this;

		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"appearanceSettings", winrt::xaml_typename<Mischief_IRC::AppearanceSettingsPage>()));
		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"ircSettings", winrt::xaml_typename<Mischief_IRC::IrcSettingsPage>()));

		settings.push_back(Setting("ircHost"));
		settings.push_back(Setting("ircPort"));
		settings.push_back(Setting("ircPass"));
		settings.push_back(Setting("ircNick"));
		settings.push_back(Setting("ircUser"));
		settings.push_back(Setting("ircRealname"));
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		FrameContent().Navigated({ this, &SettingsPage::On_Navigated });

		NavigationView().SelectedItem(NavigationView().MenuItems().GetAt(0));
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.SelectedItemContainer())
		{
			NavigationView_Navigate(winrt::unbox_value_or<winrt::hstring>(args.SelectedItemContainer().Tag(), L"").c_str(), args.RecommendedNavigationTransitionInfo());
		}
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::NavigationView_Navigate(wstring tag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo)
	{
		winrt::Windows::UI::Xaml::Interop::TypeName page;

		for (pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName> eachPage : _pages)
		{
			if (eachPage.first == tag)
			{
				page = eachPage.second;
				break;
			}
		}

		if (page.Name != L"" && page.Name != FrameContent().CurrentSourcePageType().Name)
		{
			FrameContent().Navigate(page, nullptr, navigationTransitionInfo);
		}
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::On_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
	{
		if (FrameContent().SourcePageType().Name != L"")
		{
			for (pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName> eachPage : _pages)
			{
				if (eachPage.second.Name == args.SourcePageType().Name)
				{
					for (winrt::Windows::Foundation::IInspectable eachMenuItem : NavigationView().MenuItems())
					{
						winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem navigationViewItem = eachMenuItem.try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();

						if (navigationViewItem)
						{
							winrt::hstring hstringValue = winrt::unbox_value_or<winrt::hstring>(navigationViewItem.Tag(), L"");

							if (hstringValue == eachPage.first)
							{
								NavigationView().SelectedItem(navigationViewItem);
								NavigationView().Header(navigationViewItem.Content());
							}
						}
					}

					break;
				}
			}
		}
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e)
	{
		throw winrt::hresult_error(E_FAIL, winrt::hstring(L"Failed to load page ") + e.SourcePageType().Name);
	}

	void winrt::Mischief_IRC::implementation::SettingsPage::ButtonDiscard_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::SettingsPage::ButtonSave_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}
}
