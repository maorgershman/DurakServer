#pragma once

#include <Server/server.hpp>
#include <includes.hpp>

namespace Server
{

struct ClientSocket
{
    const tstring address;
    const int port;

    ClientSocket(SocketFd socketFd, SocketAddress socketAddress);

    void client_set_timeout(long timeoutMillis) const;
    int client_recv(char* pBuffer, size_t size) const;
    void client_close() const;

    SocketFd get_socket_fd() const;
    const SocketAddress& get_socket_address() const;
};

} // namespace Server
