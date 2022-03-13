//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Mischief_IRC;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void Mischief_IRC::MainPage::OnIrcClientConnectionStatusChanged()
{
	if (_ircClient.IsConnected())
	{
		MenuFlyoutItemIrcClientConnect->IsEnabled = false;
		MenuFlyoutItemIrcClientReconnect->IsEnabled = true;
		MenuFlyoutItemIrcClientDisconnect->IsEnabled = true;
	}

	else
	{
		MenuFlyoutItemIrcClientConnect->IsEnabled = true;
		MenuFlyoutItemIrcClientReconnect->IsEnabled = false;
		MenuFlyoutItemIrcClientDisconnect->IsEnabled = false;
	}
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientConnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	_ircClient.Connect("bouncer.lan", "6667", "[REDACTED]", "JuliusZet", "JuliusZet", "JuliusZet");
	OnIrcClientConnectionStatusChanged();
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientReconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	_ircClient.Disconnect();
	_ircClient.Connect("bouncer.lan", "6667", "[REDACTED]", "JuliusZet", "JuliusZet", "JuliusZet");
	OnIrcClientConnectionStatusChanged();
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientDisconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	_ircClient.Disconnect("Bye!");
	OnIrcClientConnectionStatusChanged();
}

void Mischief_IRC::MainPage::ButtonTest_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
