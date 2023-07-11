#include "pch.h"
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

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxRdy_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxJumpcallout_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxJumpcallout_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxJumpcallout_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxJumpcallout_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxOwnPos_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxOwnPos_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSysPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPosPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFr_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxFr_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonFrPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonFrMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientOnlineStatus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxClientOnlineStatus_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInOpen_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInPg_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInSolo_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonClientInMm_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxSysconf_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxSysconf_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSysconf_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonSyscorr_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxSyscorr_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxSyscorr_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxTm_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxTm_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonTmPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonTmMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxPrep_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxPrep_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPrepPlus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonPrepMinus_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxNavcheck_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::CheckBoxNavcheck_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonNavcheckCanNotJump_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::RadioButtonNavcheckCanJump_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxNavcheckCanJump_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e)
	{

	}

	void winrt::Mischief_IRC::implementation::CalloutCreatorPage::TextBoxNavcheckCanJump_KeyDown(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e)
	{

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
