#pragma once

#include <UI/UI.hpp>

namespace UI
{
    struct Window
    {
        static void create(HINSTANCE hInstance);
        static void loop();

        static HWND get_hWnd();
    };
} // namespace UI
