#include <Network/player_client.hpp>

namespace Network
{
    PlayerClient::PlayerClient(const PrimeClient& client)
        : client(client)
    {
        std::cout << "Created a new player client for " << client.to_string() << std::endl;

        // TODO: Wait for information such as nickname (ofc limited time, consider multiple attempts)
        // If received successfully, create a player instance via the Durak interface
        // Otherwise, don't do anything and let the destructors do the work

        // Meanwhile:
        char buffer[1];
        client.socket.client_set_timeout(0);
        client.socket.client_recv(buffer, 1); // dummy
    }

    PlayerClient::~PlayerClient()
    {
        std::cout << "Destroyed the player client for " << client.to_string() << std::endl;

        // TODO: If a player was created successfully, disconnect him
    }
} // namespace Network
