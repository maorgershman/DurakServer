#include <UI/Window.hpp>

#ifdef UNICODE
#define Main wWinMain
#else
#define Main WinMain
#endif // UNICODE

#pragma warning(disable : 28251) // Inconsistent annotation on Main

int WINAPI Main(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int)
{
    UI::Window::initialize(hInstance);
    UI::Window::run();
    UI::Window::loop();
    return 0;
}