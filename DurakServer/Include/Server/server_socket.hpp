#pragma once

#include <Server/client_socket.hpp>

namespace Server
{
    struct ServerSocket
    {
        const int port;

        ServerSocket(int port);

        void server_winsock2_startup() const;
        void server_open_socket() const;
        void server_bind() const;
        void server_listen(int maxClients) const;
        void server_set_timeout(long timeoutMillis) const;
        ClientSocket server_accept() const;
        void server_close() const;
    };
} // namespace Server
