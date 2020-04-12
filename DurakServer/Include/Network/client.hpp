#pragma once

#include <Network/client_socket.hpp>

namespace Network
{
    struct Client
    {
        Client(const ClientSocket& clientSocket);
        ~Client();

        void run();
    private:
        ClientSocket clientSocket;
    };
} // namespace Network
