//
// SettingsDialog.xaml.h
// Declaration of the SettingsDialog class
//

#pragma once

#include "SettingsDialog.g.h"

namespace Mischief_IRC
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SettingsDialog sealed
	{
	public:
		SettingsDialog();
	private:
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
