#pragma once

#include <Network/prime_client.hpp>

namespace Network
{
    struct PlayerClient
    {
        const PrimeClient& client;

        PlayerClient(const PrimeClient& client);
        ~PlayerClient();
    };
} // namespace Network
