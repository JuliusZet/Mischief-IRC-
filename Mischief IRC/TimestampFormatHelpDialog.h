#pragma once

#include "TimestampFormatHelpDialog.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct TimestampFormatHelpDialog : TimestampFormatHelpDialogT<TimestampFormatHelpDialog>
    {
    public:
        TimestampFormatHelpDialog();

    private:
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct TimestampFormatHelpDialog : TimestampFormatHelpDialogT<TimestampFormatHelpDialog, implementation::TimestampFormatHelpDialog>
    {
    };
}
