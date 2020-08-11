#include <Network/server.hpp> // Changing the order will result in linker errors, thanks Windows!
#include <Durak/player.hpp>

#include <Durak/durak.hpp>
#include <UI/graphics.hpp>

#include <vector>
#include <algorithm>
#include <thread>

namespace Durak
{
    ////////////////////////////
    // Static variables

    static GameSettings gameSettings;
    static std::vector<Player*> players;

    static bool isGameLoopRunning;
    static GameState gameState;

    ////////////////////////////
    // Static functions prototypes

    static void set_state(GameState state);
    static void game_loop();

    ////////////////////////////
    // External functions definitions
    
    void load_settings(std::string&& strCmdLine)
    {
        // Parse the command line args
        {
            std::string strVariation, strPlayerCount, strSeed;
            {
                std::stringstream ss(strCmdLine);
                ss >> strVariation;
                ss >> strPlayerCount;
                ss >> strSeed;
            }

            // Variation
            if (strVariation == "Podkidnoy")
            {
                gameSettings.variation = GameSettings::Variation::Podkidnoy;
                std::cout << "Variation = Podkidnoy" << std::endl;
            }
            else if (strVariation == "Perevodnoy")
            {
                gameSettings.variation = GameSettings::Variation::Perevodnoy;
                std::cout << "Variation = Perevodnoy" << std::endl;
            }
            else
            {
                throw std::runtime_error("Invalid variation!");
                return;
            }

            // Player count
            {
                int playerCount = std::stoi(strPlayerCount); 
                if (playerCount >= 2 && playerCount <= 6)
                {
                    gameSettings.playerCount = playerCount;
                    std::cout << "Player count = " << playerCount << std::endl;
                }
                else
                {
                    throw std::runtime_error("Invalid player count: " + std::to_string(playerCount));
                    return;
                }
            }

            // Seed
            {
                // TODO: Might need to check that the seed is in proper format

                strSeed = strSeed.substr(2, 8); // 0x -> 2 chars, ffffffff -> 8 chars
                uint32_t seed = std::stoul(strSeed, nullptr, 16); // base 16

                gameSettings.seed = seed;
                std::cout << "Seed = 0x" << std::hex << seed << std::dec << std::endl;
            }
        }
    }

    void run()
    {
        Network::Server::run();

        std::thread gameThread(game_loop);
        gameThread.detach();
    }

    void close()
    {
        isGameLoopRunning = false;
        // TODO: Disconnect the connected players and free dynamic memory
        Network::Server::close();
    }

    const GameSettings& get_game_settings()
    {
        return gameSettings;
    }

    ///////////////////////////////

    void set_state(GameState state)
    {
        gameState = state;
        UI::Graphics::set_state(state);
    }

    void game_loop()
    {
        isGameLoopRunning = true;
        set_state(GameState::WaitingForPlayers);

        while (isGameLoopRunning)
        {
            UI::Graphics::render();
            Sleep(5); // 200 fps
        }
    }
} // namespace Durak
