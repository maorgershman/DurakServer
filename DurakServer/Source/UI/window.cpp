#include <UI/window.hpp>
#include <resource.hpp>

namespace UI
{
    ////////////////////////////
    // Static constant variables

    static constexpr auto strWndClassName = TEXT("DurakServer");
    static constexpr auto strWndTitle = TEXT("Durak Server");
    static constexpr auto strConsoleTitle = TEXT("Durak Server - Console");
    static constexpr auto nWndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE;
    static constexpr int nCliWidth = 1280;
    static constexpr int nCliHeight = 720;
    static constexpr int nWndWidth = nCliWidth + 16;
    static constexpr int nWndHeight = nCliHeight + 39;

    ////////////////////////////
    // Static variables

    static HINSTANCE hInstance;
    static HWND hWnd;
    static int nWndX, nWndY;

    ////////////////////////////
    // Static functions prototypes

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    ////////////////////////////
    // External functions definitions

    void Window::create(HINSTANCE hInstance_Local)
    {
        hInstance = hInstance_Local;

        // Register the window
        WNDCLASS wc{};
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
        wc.lpszClassName = strWndClassName;
        wc.lpfnWndProc = WndProc;
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        RegisterClass(&wc);
        
        // Attach a console
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        SetConsoleTitle(strConsoleTitle);

        // Set the standard input and output streams to the console
        FILE *pOutStream, *pInStream;
        freopen_s(&pInStream, "CON", "r", stdin);
        freopen_s(&pOutStream, "CON", "w", stdout);

        // Calculate the window X & Y so that it will be centered
        RECT screenRect{};
        GetClientRect(GetDesktopWindow(), &screenRect);
        nWndX = (screenRect.right - nWndWidth) / 2;
        nWndY = (screenRect.bottom - nWndHeight) / 2;

        // Create the window
        hWnd = CreateWindow(strWndClassName, strWndTitle, nWndStyle, nWndX, nWndY, nWndWidth, nWndHeight, NULL, NULL, hInstance, NULL);
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

    HWND Window::get_hWnd()
    {
        return hWnd;
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
