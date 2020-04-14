#pragma once

#include <Network/player_client.hpp>

namespace Durak
{
    struct Player
    {
        Player(Network::PlayerClient&& client);
        ~Player();
    private:
        Network::PlayerClient client;
    };
} // namespace Durak
