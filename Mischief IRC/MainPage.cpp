#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	winrt::Mischief_IRC::implementation::MainPage* MainPage::Current{ nullptr };

	winrt::Mischief_IRC::implementation::MainPage::MainPage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

		Current = this;

		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"home", winrt::xaml_typename<Mischief_IRC::HomePage>()));
		//_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"ircChannelFuelrats", winrt::xaml_typename<Mischief_IRC::IrcPage>()));
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		FrameContent().Navigated({ this, &MainPage::On_Navigated });

		NavigationView().SelectedItem(NavigationView().MenuItems().GetAt(0));
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.IsSettingsSelected())
		{
			NavigationView_Navigate(L"settings", args.RecommendedNavigationTransitionInfo());
		}

		else if (args.SelectedItemContainer())
		{
			NavigationView_Navigate(winrt::unbox_value_or<winrt::hstring>(args.SelectedItemContainer().Tag(), L"").c_str(), args.RecommendedNavigationTransitionInfo());
		}
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_Navigate(wstring tag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo)
	{
		winrt::Windows::UI::Xaml::Interop::TypeName page;

		if (tag == L"settings")
		{
			page = winrt::xaml_typename<Mischief_IRC::SettingsPage>();
		}

		else
		{
			for (pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName> eachPage : _pages)
			{
				if (eachPage.first == tag)
				{
					page = eachPage.second;
					break;
				}
			}
		}

		if (page.Name != L"" && page.Name != FrameContent().CurrentSourcePageType().Name)
		{
			FrameContent().Navigate(page, nullptr, navigationTransitionInfo);
		}
	}

	void winrt::Mischief_IRC::implementation::MainPage::On_Navigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
	{
		if (FrameContent().SourcePageType().Name == winrt::xaml_typename<Mischief_IRC::SettingsPage>().Name)
		{
			NavigationView().SelectedItem(NavigationView().SettingsItem().as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>());
			NavigationView().Header(winrt::box_value(L"Settings"));
		}

		else if (FrameContent().SourcePageType().Name != L"")
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

	void winrt::Mischief_IRC::implementation::MainPage::FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e)
	{
		throw winrt::hresult_error(E_FAIL, winrt::hstring(L"Failed to load page ") + e.SourcePageType().Name);
	}

	void winrt::Mischief_IRC::implementation::MainPage::IrcConnect()
	{
		_ircClient.Connect(Settings::Get("ircHost"), Settings::Get("ircPort"), Settings::Get("ircPass"), Settings::Get("ircNick"), Settings::Get("ircUser"), Settings::Get("ircRealname"));
	}

	void winrt::Mischief_IRC::implementation::MainPage::IrcDisconnect()
	{
		_ircClient.Disconnect("Bye!");
	}
}
