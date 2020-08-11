#include <Network/client_socket.hpp>

namespace Network
{
    ////////////////////////////
    // Static variables

    static SocketFd socketFd;
    static SocketAddress socketAddress;

    ////////////////////////////
    // Static functions prototypes

    static std::string load_address(const SocketAddress& socketAddress);
    static int load_port(const SocketAddress& socketAddress);

    ////////////////////////////
    // External functions definitions

    ClientSocket::ClientSocket(SocketFd socketFd_Local, SocketAddress socketAddress_Local)
        : address(load_address(socketAddress_Local)), port(load_port(socketAddress_Local))
    {
        socketFd = socketFd_Local;
        socketAddress = socketAddress_Local;
    }

    int ClientSocket::client_recv(char* pBuffer, size_t size) const
    {
        return recv(socketFd, pBuffer, size, 0);
    }

    void ClientSocket::client_set_timeout(long timeoutMillis) const
    {
        if (setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeoutMillis), sizeof(timeval)) == -1)
        {
            throw std::runtime_error("Unable to set socket timeout!");
        }
    }

    void ClientSocket::client_close() const
    {
        if (socketFd != -1)
        {
            shutdown(socketFd, SD_BOTH);
            closesocket(socketFd);
        }
    }

    SocketFd ClientSocket::get_socket_fd() const
    {
        return socketFd;
    }

    const SocketAddress& ClientSocket::get_socket_address() const
    {
        return socketAddress;
    }

    const std::string ClientSocket::to_string() const
    {
        return address + ":" + std::to_string(port);
    }

    ////////////////////////////
    // Static functions definitions

    std::string load_address(const SocketAddress& socketAddress)
    {
        char buffer[4 * 3 + 3 + 1]; // XXX.XXX.XXX.XXX
        inet_ntop(AF_INET, &socketAddress.sin_addr, buffer, sizeof(buffer) / sizeof(char));
        return buffer;
    }

    int load_port(const SocketAddress& socketAddress)
    {
        return htons(socketAddress.sin_port);
    }
} // namespace Server
