#include <durak.hpp>
#include <UI/window.hpp>
#include <UI/graphics.hpp>

int WINAPI Main(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int)
{
    // Initialize the window and console before the game so that output will be possible!
    UI::Window::create(hInstance);
    Durak::initialize(lpCmdLine);
    UI::Graphics::initialize();
    UI::Window::loop();
    UI::Graphics::cleanup();
    Durak::cleanup();
    return 0;
}
