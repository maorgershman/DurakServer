#include <UI/window.hpp>
#include <UI/graphics.hpp>
#include <Durak/durak.hpp>

namespace UI
{
    ////////////////////////////
    // Static functions prototypes

    static void terminate();

    ////////////////////////////
    // External functions definitions

    void create(HINSTANCE hInstance)
    {
        Window::create(hInstance);
        Graphics::initialize();
    }

    void run()
    {
        Window::loop();
    }

    void on_console_close()
    {
        terminate();
    }

    void on_window_close()
    {
        terminate();
    }

    ////////////////////////////
    // Static functions definitions

    void terminate()
    {
        Durak::close();

        constexpr int seconds = 1;
        for (int i = seconds; i > 0; i--)
        {
            tcout << T("Terminating in ") << i << T(" seconds...") << endl;
            Sleep(1000);
        }

        ExitProcess(0);
    }
} // namespace UI
