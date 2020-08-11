#include <UI/window.hpp>
#include <UI/graphics.hpp>
#include <Durak/durak.hpp>

namespace UI
{
    ////////////////////////////
    // External functions definitions

    void create(HINSTANCE hInstance)
    {
        try
        {
            Window::create(hInstance);
            Graphics::initialize();
        }
        catch (const std::runtime_error& err)
        {
            throw err;
        }
    }

    void run()
    {
        Window::loop();
    }

    void on_console_close()
    {
        terminate(1);
    }

    void on_window_close()
    {
        terminate(1);
    }

    void terminate(int seconds)
    {
        Durak::close();

        for (int i = seconds; i > 0; i--)
        {
            std::cout << "Terminating in " << i << " seconds..." << std::endl;
            Sleep(1000);
        }

        ExitProcess(0);
    }
} // namespace UI
