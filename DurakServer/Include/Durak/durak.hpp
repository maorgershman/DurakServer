#pragma once

#include <includes.hpp>

namespace Durak
{
    struct GameSettings
    {
        enum class Variation
        {
            Podkidnoy, Perevodnoy
        };

        Variation variation;
        int       playerCount;
        uint32_t  seed;
    };

    enum class GameState : uint8_t
    {
        Undetermined = 0xff,
        WaitingForPlayers = 0x00
    };

    void load_settings(std::string&& strCmdLine);
    void run();
    void close();

    const GameSettings& get_game_settings();
}; // namespace Durak
