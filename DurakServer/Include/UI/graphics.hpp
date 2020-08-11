#pragma once

#include <Durak/durak.hpp>
#include <UI/UI.hpp>

namespace UI
{
    struct Graphics
    {
        static void initialize();
        static void render();
        static void cleanup();

        static void set_state(Durak::GameState state);
    };
} // namespace UI
