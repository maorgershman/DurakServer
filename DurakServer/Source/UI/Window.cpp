#include <UI/Window.hpp>
#include <resource.h>

namespace UI
{
    ////////////////////////////
    // Static constant variables

    static constexpr auto strWindowClassName = TEXT("DurakServer");
    static constexpr auto strWindowTitle = TEXT("Durak Server");

    ////////////////////////////
    // Static variables

    static HINSTANCE hInstance;

    ////////////////////////////
    // Static functions prototypes

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    ////////////////////////////
    // Link external variables

    HWND Window::hWnd;

    ////////////////////////////
    // External functions definitions

    void Window::initialize(HINSTANCE hInstance_Local)
    {
        hInstance = hInstance_Local;

        WNDCLASS wc{};
        wc.lpszClassName = strWindowClassName;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
        wc.lpfnWndProc = WndProc;
        RegisterClass(&wc);
    }

    void Window::run()
    {
        hWnd = CreateWindow(strWindowClassName, strWindowTitle, 
            WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
            100, 100, 800, 600, NULL, NULL, hInstance, NULL);
    }

    void Window::loop()
    {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    ////////////////////////////
    // Static functions definitions

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            case WM_CLOSE:
            {
                PostQuitMessage(0);
            } break;
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
} // namespace UI
