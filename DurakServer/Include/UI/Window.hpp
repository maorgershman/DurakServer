#pragma once

#include <Windows.h>

namespace UI
{
    struct Window
    {
        static HWND hWnd;

        static void initialize(HINSTANCE hInstance);
        static void run();
        static void loop();
    };
} // namespace UI
