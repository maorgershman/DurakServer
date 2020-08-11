#pragma once

#include <Network/client_socket.hpp>

namespace Network
{
    struct PrimeClient
    {
        const ClientSocket socket;

        PrimeClient(ClientSocket&& socket);
        ~PrimeClient();

        const std::string to_string() const;
    };
} // namespace Network
