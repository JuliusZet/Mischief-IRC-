//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "Backend/IrcClient.h"
#include "Backend/Settings.h"
#include "MainPage.g.h"

namespace Mischief_IRC
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void OnIrcClientConnectionStatusChanged();

	private:
		IrcClient _ircClient;
		void MenuFlyoutItemIrcClientConnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MenuFlyoutItemIrcClientReconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MenuFlyoutItemIrcClientDisconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
