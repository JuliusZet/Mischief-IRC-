#include "pch.h"
#include "TimestampFormatHelpDialog.h"
#if __has_include("TimestampFormatHelpDialog.g.cpp")
#include "TimestampFormatHelpDialog.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Mischief_IRC::implementation
{
    winrt::Mischief_IRC::implementation::TimestampFormatHelpDialog::TimestampFormatHelpDialog()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
    }
}
