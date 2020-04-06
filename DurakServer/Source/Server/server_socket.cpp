#include <Server/server_socket.hpp>

namespace Server
{

    ////////////////////////////
    // Static variables

    static WSADATA wsad;
    static SocketFd socketFd = -1;
    static SocketAddress socketAddress;

    ////////////////////////////
    // External functions definitions

    ServerSocket::ServerSocket(int port)
        : port(port)
    {
        socketAddress = { AF_INET, htons(port), {INADDR_ANY} };
    }

    void ServerSocket::server_winsock2_startup() const
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsad))
        {
            throw std::runtime_error("Unable to start WinSock2.2!");
        }
    }

    void ServerSocket::server_open_socket() const
    {
        socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFd == -1)
        {
            throw std::runtime_error("Unable to open socket!");
        }
    }

    void ServerSocket::server_bind() const
    {
        auto pSocketAddress = reinterpret_cast<const sockaddr*>(&socketAddress);
        auto result = bind(socketFd, pSocketAddress, sizeof(SocketAddress));
        if (result == -1)
        {
            throw std::runtime_error("Unable to bind socket to address!");
        }
    }

    void ServerSocket::server_listen(int maxClients) const
    {
        if (listen(socketFd, maxClients) == -1)
        {
            throw std::runtime_error("Unable to listen to the socket!");
        }
    }

    void ServerSocket::server_set_timeout(long timeoutMillis) const
    {
        if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO | SO_SNDTIMEO, reinterpret_cast<const char*>(&timeoutMillis), sizeof(timeval)) == -1)
        {
            throw std::runtime_error("Unable to set socket timeout!");
        }
    }

    ClientSocket ServerSocket::server_accept() const
    {
        SocketAddress clientSocketAddress;
        int addressSize = sizeof(SocketAddress);
        auto pClientSocketAddress = reinterpret_cast<sockaddr*>(&clientSocketAddress);

        SocketFd clientSocketFd = accept(socketFd, pClientSocketAddress, &addressSize);
        if (clientSocketFd == -1)
        {
            throw std::runtime_error("Can't accept new connection!");
        }

        return ClientSocket(clientSocketFd, clientSocketAddress);
    }

    void ServerSocket::server_close() const
    {
        if (socketFd != -1)
        {
            shutdown(socketFd, SD_BOTH);
            closesocket(socketFd);
            WSACleanup();
        }
    }

} // namespace Server
