#pragma once

#include <includes.hpp>
#include <game_settings.hpp>

struct Durak
{
    static void initialize(LPTSTR lpCmdLine);
    static void cleanup();

    static const GameSettings &get_game_settings();
};
