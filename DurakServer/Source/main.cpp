#include <UI/UI.hpp>
#include <Durak/durak.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR pCmdLine, int)
{
    try
    {
        UI::create(hInstance); // Create the UI
        Durak::load_settings(pCmdLine); // Load the game settings
        Durak::run();
        UI::run();
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "Error: " << err.what() << std::endl;
        UI::terminate(10);
    }
    return 0;
}
