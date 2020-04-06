#pragma once

#include <WS2tcpip.h>

using SocketFd = int;
using SocketAddress = sockaddr_in;

namespace Server
{
    void run();
    void close();

    bool is_open();
}; // namespace Server
