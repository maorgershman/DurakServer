#pragma once

#include <includes.hpp>

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
