#pragma once

#include "IrcPage.g.h"

namespace winrt::Mischief_IRC::implementation
{
    struct IrcPage : IrcPageT<IrcPage>
    {
    private:

    public:
        IrcPage();
    };
}

namespace winrt::Mischief_IRC::factory_implementation
{
    struct IrcPage : IrcPageT<IrcPage, implementation::IrcPage>
    {
    };
}
