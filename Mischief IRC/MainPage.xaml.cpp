//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Backend/IrcSocket.h"

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

IrcSocket ircSocket;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientConnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ircSocket.Connect("bouncer.lan", "6667");
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientReconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ircSocket.Disconnect();
	ircSocket.Connect("bouncer.lan", "6667");
}

void Mischief_IRC::MainPage::MenuFlyoutItemIrcClientDisconnect_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ircSocket.Disconnect();
}
