#pragma once

#include <UI/UI.hpp>

namespace UI
{
    struct Window
    {
        static constexpr int width = 1280;
        static constexpr int height = 720;

        static void create(HINSTANCE hInstance);
        static void loop();

        static HWND get_hWnd();
    };
} // namespace UI
