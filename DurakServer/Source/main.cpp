#include <UI/UI.hpp>
#include <Durak/durak.hpp>

int WINAPI tmain(HINSTANCE hInstance, HINSTANCE, PTSTR pCmdLine, int)
{
    UI::create(hInstance); // Create the UI
    Durak::load_settings(pCmdLine); // Load the game settings
    Durak::run();
    UI::run();
    return 0;
}
