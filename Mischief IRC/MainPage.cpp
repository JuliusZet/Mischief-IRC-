#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	void MainPage::OnIrcClientConnectionStatusChanged()
	{
		if (ircClient.IsConnected())
		{
			this->MenuFlyoutItemIrcClientConnect().IsEnabled(false);
			this->MenuFlyoutItemIrcClientReconnect().IsEnabled(true);
			this->MenuFlyoutItemIrcClientDisconnect().IsEnabled(true);
		}

		else
		{
			this->MenuFlyoutItemIrcClientConnect().IsEnabled(true);
			this->MenuFlyoutItemIrcClientReconnect().IsEnabled(false);
			this->MenuFlyoutItemIrcClientDisconnect().IsEnabled(false);
		}
	}

	void MainPage::MenuFlyoutItemMischiefIrcSettings_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ContentDialog settingsDialog{};
		settingsDialog.Content(SettingsDialog());
		settingsDialog.Title(box_value(L"Settings"));
		settingsDialog.FullSizeDesired(true);
		settingsDialog.ShowAsync();
	}

	void MainPage::MenuFlyoutItemMischiefIrcExit_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{

	}

	void MainPage::MenuFlyoutItemIrcClientConnect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ircClient.Connect("bouncer.lan", "6667", "[REDACTED]", "JuliusZet", "JuliusZet", "JuliusZet");
		thread receiveThread = ircClient.ReceiveAsync();
		receiveThread.detach();
		OnIrcClientConnectionStatusChanged();
	}

	void MainPage::MenuFlyoutItemIrcClientReconnect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ircClient.Reconnect("bouncer.lan", "6667", "[REDACTED]", "JuliusZet", "JuliusZet", "JuliusZet");
		thread receiveThread = ircClient.ReceiveAsync();
		receiveThread.detach();
		OnIrcClientConnectionStatusChanged();
	}

	void MainPage::MenuFlyoutItemIrcClientDisconnect_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		ircClient.Disconnect("Bye!");
		OnIrcClientConnectionStatusChanged();
	}
}
