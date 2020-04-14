#include <Network/server.hpp> // Changing the order will result in linker errors, thanks Windows!
#include <Durak/player.hpp>

#include <Durak/durak.hpp>

#include <vector>
#include <algorithm>

namespace Durak
{
    ////////////////////////////
    // Static variables

    static GameSettings gameSettings;
    static std::vector<Player*> players;

    ////////////////////////////
    // External functions definitions
    
    void load_settings(tstring&& strCmdLine)
    {
        // Parse the command line args
        {
            tstring strVariation, strPlayerCount, strSeed;
            {
                tstringstream ss(strCmdLine);
                ss >> strVariation;
                ss >> strPlayerCount;
                ss >> strSeed;
            }

            // Variation
            if (strVariation == T("Podkidnoy"))
            {
                gameSettings.variation = GameSettings::Variation::Podkidnoy;
                tcout << T("Variation = Podkidnoy") << endl;
            }
            else if (strVariation == T("Perevodnoy"))
            {
                gameSettings.variation = GameSettings::Variation::Perevodnoy;
                tcout << T("Variation = Perevodnoy") << endl;
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
                    tcout << T("Player count = ") << playerCount << endl;
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
                tcout << T("Seed = 0x") << std::hex << seed << std::dec << endl;
            }
        }
    }

    void run()
    {
        // TODO: Start a game thread
        Network::Server::run();
    }

    void close()
    {
        // TODO: Disconnect the connected players and free dynamic memory
        Network::Server::close();
    }

    const GameSettings& get_game_settings()
    {
        return gameSettings;
    }
} // namespace Durak
