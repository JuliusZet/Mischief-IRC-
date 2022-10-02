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

		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"Home", winrt::xaml_typename<Mischief_IRC::HomePage>()));
		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(L"IRC", winrt::xaml_typename<Mischief_IRC::IrcPage>()));
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		FrameContent().Navigated({ this, &MainPage::OnNavigated });

		NavigationView().SelectedItem(NavigationView().MenuItems().GetAt(0));
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		if (args.IsSettingsSelected())
		{
			NavigationView_Navigate(L"Settings", args.RecommendedNavigationTransitionInfo());
		}

		else if (args.SelectedItemContainer())
		{
			NavigationView_Navigate(winrt::unbox_value_or<winrt::hstring>(args.SelectedItemContainer().Tag(), L"").c_str(), args.RecommendedNavigationTransitionInfo());
		}
	}

	void winrt::Mischief_IRC::implementation::MainPage::NavigationView_Navigate(wstring tag, winrt::Windows::UI::Xaml::Media::Animation::NavigationTransitionInfo const& navigationTransitionInfo)
	{
		winrt::Windows::UI::Xaml::Interop::TypeName page;

		if (tag == L"Settings")
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

		if (page.Name != L"")
		{
			FrameContent().Navigate(page, nullptr, navigationTransitionInfo);
		}
	}

	void winrt::Mischief_IRC::implementation::MainPage::OnNavigated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& args)
	{
		winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem navigationViewItem = NavigationView().SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();

		if (navigationViewItem)
		{
			NavigationView().Header(navigationViewItem.Content());
		}
	}

	void winrt::Mischief_IRC::implementation::MainPage::FrameContent_NavigationFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const& e)
	{
		throw winrt::hresult_error(E_FAIL, winrt::hstring(L"Failed to load page ") + e.SourcePageType().Name);
	}

	void winrt::Mischief_IRC::implementation::MainPage::IrcConnect()
	{
		IrcClient.Connect(Settings::Get("ircHost"), Settings::Get("ircPort"), Settings::Get("ircPass"), Settings::Get("ircNick"), Settings::Get("ircUser"), Settings::Get("ircRealname"));
	}

	void winrt::Mischief_IRC::implementation::MainPage::IrcDisconnect()
	{
		IrcClient.Disconnect("Bye!");
	}

	void winrt::Mischief_IRC::implementation::MainPage::IrcAddChannel(string channelName)
	{
		Microsoft::UI::Xaml::Controls::NavigationViewItem navigationViewItem;
		navigationViewItem.Tag(winrt::box_value(to_hstring(channelName)));
		navigationViewItem.Content(navigationViewItem.Tag());

		winrt::Windows::UI::Xaml::Controls::FontIcon fontIcon = winrt::Windows::UI::Xaml::Controls::FontIcon{};
		fontIcon.FontFamily(winrt::Windows::UI::Xaml::Media::FontFamily{ L"Segoe UI" });

		if (channelName == "#fuelrats")
		{
			fontIcon.Glyph(L"#fr");
		}
		else if (channelName == "#ratchat")
		{
			fontIcon.Glyph(L"#rc");
		}
		else if (channelName == "#debrief")
		{
			fontIcon.Glyph(L"#db");
		}
		else
		{
			fontIcon.Glyph(to_hstring(channelName.substr(0, 3)));
		}

		navigationViewItem.Icon(fontIcon);

		NavigationView().MenuItems().Append(navigationViewItem);

		_pages.push_back(make_pair<wstring, winrt::Windows::UI::Xaml::Interop::TypeName>(wstring(to_hstring(channelName)), winrt::xaml_typename<Mischief_IRC::IrcPage>()));
	}
}
