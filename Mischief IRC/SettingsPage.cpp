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

		settings.push_back(Setting("appearanceTheme"));
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

	winrt::Windows::Foundation::IAsyncAction winrt::Mischief_IRC::implementation::SettingsPage::ButtonSave_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		bool foundChangedSetting{};
		hstring changelog{ L"You have changed the following settings:\n\n" };

		for (Setting eachSetting : settings)
		{
			if (eachSetting.savedValue != eachSetting.newValue)
			{
				foundChangedSetting = true;

				if (eachSetting.key != "ircPass")
				{
					changelog = changelog + to_hstring(eachSetting.key) + L": \"" + eachSetting.savedValue + L"\" --> \"" + eachSetting.newValue + L"\"\n";
				}

				else
				{
					changelog = changelog + to_hstring(eachSetting.key) + L": \"[REDACTED]\" --> \"[REDACTED]\"\n";
				}
			}
		}

		if (foundChangedSetting)
		{
			winrt::Windows::UI::Xaml::Controls::ContentDialog dialogConfirmation;
			dialogConfirmation.Title(box_value(L"Do you really want to save the changed settings?"));
			dialogConfirmation.Content(box_value(changelog));
			dialogConfirmation.PrimaryButtonText(L"Yes, save");
			dialogConfirmation.CloseButtonText(L"No, do not save");
			dialogConfirmation.DefaultButton(winrt::Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			auto result = co_await dialogConfirmation.ShowAsync();

			if (result == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::Primary)
			{
				for (size_t i{}; i != settings.size(); ++i)
				{
					if (settings.at(i).savedValue != settings.at(i).newValue)
					{
						settings.at(i).savedValue = settings.at(i).newValue;
						Settings::Set(settings.at(i).key, to_string(settings.at(i).newValue));

						if (settings.at(i).key == "appearanceTheme")
						{
							MainPage::Current->InfoBar().Title(L"App restart required");
							MainPage::Current->InfoBar().Message(L"Please restart the application to apply the new theme.");
							MainPage::Current->InfoBar().IsOpen(true);
						}
					}
				}

				FrameContent().Navigate(FrameContent().SourcePageType());
			}
		}

		else
		{
			winrt::Windows::UI::Xaml::Controls::ContentDialog dialogInformation;
			dialogInformation.Title(box_value(L"There are no settings to save."));
			dialogInformation.CloseButtonText(L"OK");
			dialogInformation.DefaultButton(winrt::Windows::UI::Xaml::Controls::ContentDialogButton::Close);

			auto result = co_await dialogInformation.ShowAsync();
		}
	}

	winrt::Windows::Foundation::IAsyncAction winrt::Mischief_IRC::implementation::SettingsPage::ButtonDiscard_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		bool foundChangedSetting{};
		hstring changelog{ L"You have changed the following settings:\n\n" };

		for (Setting eachSetting : settings)
		{
			if (eachSetting.newValue != eachSetting.savedValue)
			{
				foundChangedSetting = true;

				if (eachSetting.key != "ircPass")
				{
					changelog = changelog + to_hstring(eachSetting.key) + L": \"" + eachSetting.savedValue + L"\" --> \"" + eachSetting.newValue + L"\"\n";
				}

				else
				{
					changelog = changelog + to_hstring(eachSetting.key) + L": \"[REDACTED]\" --> \"[REDACTED]\"\n";
				}
			}
		}

		if (foundChangedSetting)
		{
			winrt::Windows::UI::Xaml::Controls::ContentDialog dialogConfirmation;
			dialogConfirmation.Title(box_value(L"Do you really want to discard the changed settings?"));
			dialogConfirmation.Content(box_value(changelog));
			dialogConfirmation.PrimaryButtonText(L"Yes, discard");
			dialogConfirmation.CloseButtonText(L"No, do not discard");
			dialogConfirmation.DefaultButton(winrt::Windows::UI::Xaml::Controls::ContentDialogButton::Primary);

			auto result = co_await dialogConfirmation.ShowAsync();

			if (result == winrt::Windows::UI::Xaml::Controls::ContentDialogResult::Primary)
			{
				for (size_t i{}; i != settings.size(); ++i)
				{
					if (settings.at(i).newValue != settings.at(i).savedValue)
					{
						settings.at(i).newValue = settings.at(i).savedValue;
					}
				}

				FrameContent().Navigate(FrameContent().SourcePageType());
			}
		}

		else
		{
			winrt::Windows::UI::Xaml::Controls::ContentDialog dialogInformation;
			dialogInformation.Title(box_value(L"There are no settings to discard."));
			dialogInformation.CloseButtonText(L"OK");
			dialogInformation.DefaultButton(winrt::Windows::UI::Xaml::Controls::ContentDialogButton::Close);

			auto result = co_await dialogInformation.ShowAsync();
		}
	}
}
