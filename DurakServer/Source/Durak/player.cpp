#include <Durak/player.hpp>

namespace Durak
{
    Player::Player(Network::PlayerClient&& client)
        : client(client)
    {
    }

    Player::~Player()
    {
    }
} // namespace Durak
