#pragma once

#include <WS2tcpip.h>

using SocketFd = int;
using SocketAddress = sockaddr_in;

namespace Network
{
    struct Server
    {
        static void run();
        static void close();
    };
}; // namespace Network
