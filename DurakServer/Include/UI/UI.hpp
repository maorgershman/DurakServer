#pragma once

#include <Windows.h>

namespace UI
{
    void create(HINSTANCE hInstance);
    void run();
    void terminate(int seconds = 0);

    void on_console_close();
    void on_window_close();
} // namespace UI
