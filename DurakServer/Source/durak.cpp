#include <durak.hpp>

////////////////////////////
// Static variables

static GameSettings gameSettings;

////////////////////////////
// External functions definitions

void Durak::initialize(LPTSTR lpCmdLine)
{
    // Parse the command line args
    {
        string strVariation, strPlayerCount, strSeed;
        {
            stringstream ss(lpCmdLine);
            ss >> strVariation;
            ss >> strPlayerCount;
            ss >> strSeed;
        }

        // Variation
        if (strVariation == TEXT("Podkidnoy"))
        {
            gameSettings.variation = GameSettings::Variation::Podkidnoy;
            cout << TEXT("Variation = Podkidnoy") << endl;
        }
        else if (strVariation == TEXT("Perevodnoy"))
        {
            gameSettings.variation = GameSettings::Variation::Perevodnoy;
            cout << TEXT("Variation = Perevodnoy") << endl;
        }
        else
        {
            cout << TEXT("Invalid variation!") << endl;
            return;
        }

        // Player count
        {
            int playerCount = std::stoi(strPlayerCount);
            if (playerCount >= 2 && playerCount <= 6)
            {
                gameSettings.playerCount = playerCount;
                cout << TEXT("Player count = ") << playerCount << endl;
            }
            else
            {
                cout << TEXT("Invalid player count: ") << playerCount << endl;
                return;
            }
        }

        // Seed
        {
            // TODO: Might need to check that the seed is in proper format

            strSeed = strSeed.substr(2, 8); // 0x -> 2 chars, ffffffff -> 8 chars
            uint32_t seed = std::stoul(strSeed, nullptr, 16); // base 16

            gameSettings.seed = seed;
            cout << TEXT("Seed = 0x") << std::hex << seed << endl;
        }
    }
}

void Durak::cleanup()
{

}

const GameSettings& Durak::get_game_settings()
{
    return gameSettings;
}
