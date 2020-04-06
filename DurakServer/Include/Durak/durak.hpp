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

    void load_settings(tstring&& strCmdLine);
    void run();
    void close();

    const GameSettings& get_game_settings();
}; // namespace Durak
