﻿#include "pch.h"
#include "CalloutCreatorPage.h"
#if __has_include("CalloutCreatorPage.g.cpp")
#include "CalloutCreatorPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
	winrt::Mischief_IRC::implementation::CalloutCreatorPage::CalloutCreatorPage()
	{
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxCasenumber_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Prepend("Casenumber");
		TextBoxCasenumber().Focus(FocusState::Programmatic);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxCasenumber_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Casenumber");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBoxCasenumber().Text(L"");
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxCasenumber_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{
		if (TextBoxCasenumber().Text() != L"")
		{
			CheckBoxCasenumber().IsChecked(true);
			Callout::Replace("Casenumber", '#' + to_string(TextBoxCasenumber().Text()));
			TextBoxMessage().Text(to_hstring(Callout::Generate()));
		}

		else
		{
			CheckBoxCasenumber().IsChecked(false);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxCasenumber_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
		if (e.Key() == winrt::Windows::System::VirtualKey::Enter)
		{
			TextBoxJumpcallout().Focus(FocusState::Programmatic);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxRgr_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Rgr", "rgr");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxRgr_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Rgr");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxRdy_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Rdy", "rdy");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxRdy_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Rdy");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxJumpcallout_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Jumpcallout");
		TextBoxJumpcallout().Focus(FocusState::Programmatic);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxJumpcallout_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Jumpcallout");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBoxJumpcallout().Text(L"");
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxJumpcallout_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{
		if (TextBoxJumpcallout().Text() != L"")
		{
			CheckBoxJumpcallout().IsChecked(true);
			Callout::Replace("Jumpcallout", to_string(TextBoxJumpcallout().Text()) + 'j');
			TextBoxMessage().Text(to_hstring(Callout::Generate()));
		}

		else
		{
			CheckBoxJumpcallout().IsChecked(false);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxJumpcallout_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
		if (e.Key() == winrt::Windows::System::VirtualKey::Enter)
		{
			TextBoxMessage().Focus(FocusState::Programmatic);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxOwnPos_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("OwnPos");

		if (RadioButtonPosPlus().IsChecked().GetBoolean() == false)
		{
			RadioButtonSysPlus().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxOwnPos_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("OwnPos");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonSysPlus().IsChecked(false);
		RadioButtonPosPlus().IsChecked(false);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSysPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxOwnPos().IsChecked(true);
		Callout::Replace("OwnPos", "sys+");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPosPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxOwnPos().IsChecked(true);
		Callout::Replace("OwnPos", "pos+");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFr_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Fr");

		if (RadioButtonFrMinus().IsChecked().GetBoolean() == false)
		{
			RadioButtonFrPlus().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFr_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Fr");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonFrPlus().IsChecked(false);
		RadioButtonFrMinus().IsChecked(false);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonFrPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxFr().IsChecked(true);
		Callout::Replace("Fr", "fr+");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonFrMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxFr().IsChecked(true);
		Callout::Replace("Fr", "fr-");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientOnlineStatus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("ClientOnlineStatus");

		if (RadioButtonClientInPg().IsChecked().GetBoolean() == false && RadioButtonClientInSolo().IsChecked().GetBoolean() == false && RadioButtonClientInMm().IsChecked().GetBoolean() == false)
		{
			RadioButtonClientInOpen().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientOnlineStatus_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("ClientOnlineStatus");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonClientInOpen().IsChecked(false);
		RadioButtonClientInPg().IsChecked(false);
		RadioButtonClientInSolo().IsChecked(false);
		RadioButtonClientInMm().IsChecked(false);
		TextBlockClientOnlineStatus().Opacity(1.0);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInOpen_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxClientOnlineStatus().IsChecked(true);
		Callout::Replace("ClientOnlineStatus", "client in open");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBlockClientOnlineStatus().Opacity(0.0);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInPg_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxClientOnlineStatus().IsChecked(true);
		Callout::Replace("ClientOnlineStatus", "client in pg");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBlockClientOnlineStatus().Opacity(0.0);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInSolo_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxClientOnlineStatus().IsChecked(true);
		Callout::Replace("ClientOnlineStatus", "client in solo");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBlockClientOnlineStatus().Opacity(0.0);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInMm_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxClientOnlineStatus().IsChecked(true);
		Callout::Replace("ClientOnlineStatus", "client in mm");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		TextBlockClientOnlineStatus().Opacity(0.0);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxSysconf_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Sysconf");

		if (RadioButtonSyscorr().IsChecked().GetBoolean() == false)
		{
			RadioButtonSysconf().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxSysconf_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Sysconf");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonSysconf().IsChecked(false);
		RadioButtonSyscorr().IsChecked(false);
		TextBoxSyscorr().Text(L"");
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSysconf_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxSysconf().IsChecked(true);
		Callout::Replace("Sysconf", "sysconf");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSyscorr_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxSysconf().IsChecked(true);
		TextBoxSyscorr().Focus(FocusState::Programmatic);
		Callout::Replace("Sysconf", "sys " + to_string(TextBoxCasenumber().Text()) + ' ' + to_string(TextBoxSyscorr().Text()));
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxSyscorr_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{
		if (TextBoxSyscorr().Text() != L"")
		{
			RadioButtonSyscorr().IsChecked(true);
			Callout::Replace("Sysconf", "sys " + to_string(TextBoxCasenumber().Text()) + ' ' + to_string(TextBoxSyscorr().Text()));
			TextBoxMessage().Text(to_hstring(Callout::Generate()));
		}

		else
		{
			CheckBoxSysconf().IsChecked(false);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxSyscorr_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
		if (e.Key() == winrt::Windows::System::VirtualKey::Enter)
		{
			TextBoxMessage().Focus(FocusState::Programmatic);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxTm_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Tm");

		if (RadioButtonTmMinus().IsChecked().GetBoolean() == false)
		{
			RadioButtonTmPlus().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxTm_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Tm");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonTmPlus().IsChecked(false);
		RadioButtonTmMinus().IsChecked(false);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonTmPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxTm().IsChecked(true);
		Callout::Replace("Tm", "tm+");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonTmMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxTm().IsChecked(true);
		Callout::Replace("Tm", "tm-");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxPrep_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Prep");

		if (RadioButtonPrepMinus().IsChecked().GetBoolean() == false)
		{
			RadioButtonPrepPlus().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxPrep_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Prep");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonPrepPlus().IsChecked(false);
		RadioButtonPrepMinus().IsChecked(false);
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPrepPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxPrep().IsChecked(true);
		Callout::Replace("Prep", "prep+");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPrepMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxPrep().IsChecked(true);
		Callout::Replace("Prep", "prep-");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxNavcheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Append("Navcheck");

		if (RadioButtonNavcheckCanJump().IsChecked().GetBoolean() == false)
		{
			RadioButtonNavcheckCanNotJump().IsChecked(true);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxNavcheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Callout::Remove("Navcheck");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
		RadioButtonNavcheckCanNotJump().IsChecked(false);
		RadioButtonNavcheckCanJump().IsChecked(false);
		TextBoxNavcheckCanJump().Text(L"");
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonNavcheckCanNotJump_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxNavcheck().IsChecked(true);
		Callout::Replace("Navcheck", "navcheck: client can not jump");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonNavcheckCanJump_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		CheckBoxNavcheck().IsChecked(true);
		TextBoxNavcheckCanJump().Focus(FocusState::Programmatic);
		Callout::Replace("Navcheck", "navcheck: client can jump " + to_string(TextBoxNavcheckCanJump().Text()) + " ly");
		TextBoxMessage().Text(to_hstring(Callout::Generate()));
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxNavcheckCanJump_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{
		if (TextBoxNavcheckCanJump().Text() != L"")
		{
			RadioButtonNavcheckCanJump().IsChecked(true);
			Callout::Replace("Navcheck", "navcheck: client can jump " + to_string(TextBoxNavcheckCanJump().Text()) + " ly");
			TextBoxMessage().Text(to_hstring(Callout::Generate()));
		}

		else
		{
			CheckBoxNavcheck().IsChecked(false);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxNavcheckCanJump_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{
		if (e.Key() == winrt::Windows::System::VirtualKey::Enter)
		{
			TextBoxMessage().Focus(FocusState::Programmatic);
		}
	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxBc_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxBc_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonBcPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonBcMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxInst_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxInst_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonInstPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonInstMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientPos_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientPos_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientPosInEz_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientPosInSc_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxDistance_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxDistance_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxDistance_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxDistance_PreviewKeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxDistance_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ComboBoxDistance_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ComboBoxDistance_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFuelPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFuelPlus_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ButtonShowCase_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ButtonShowCaseList_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ButtonReset_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxMessage_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::ButtonSend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}
}
