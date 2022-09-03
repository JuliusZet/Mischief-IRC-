#include "pch.h"
#include "HomePage.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	winrt::Mischief_IRC::implementation::HomePage::HomePage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	void winrt::Mischief_IRC::implementation::HomePage::ButtonIrcConnect_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		_ircClient.Connect("bouncer.lan", "6667", "[REDACTED]", "JuliusZet", "JuliusZet", "JuliusZet");
		thread receiveThread = _ircClient.ReceiveAsync();
		receiveThread.detach();
	}
}
