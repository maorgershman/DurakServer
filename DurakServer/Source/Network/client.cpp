#include <Network/client.hpp>

namespace Network
{
    Client::Client(const ClientSocket& clientSocket)
        : clientSocket(clientSocket)
    {
        tcout << T("Created a new client for ") <<
            clientSocket.address << T(":") << clientSocket.port << endl;
    }

    void Client::run()
    {
        char buffer[1]; // dummy
        clientSocket.client_set_timeout(0);
        clientSocket.client_recv(buffer, sizeof(buffer));
    }

    Client::~Client()
    {
        tcout << T("Destroyed the client for ") <<
            clientSocket.address << T(":") << clientSocket.port << endl;
    }
} // namespace Network
