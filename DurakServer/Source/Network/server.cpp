#include <Network/server_socket.hpp>
#include <Network/client.hpp>

#include <thread>
#include <vector>
#include <algorithm>

namespace Network
{
    ////////////////////////////
    // Static constant variables

    static constexpr int maxClients = 6;
    static constexpr int port = 8888;

    static constexpr auto magicEntryPacket = 0xdeadbeef/*cafebabe*/;

    ////////////////////////////
    // Static variables

    static bool isOpen = false;
    static ServerSocket serverSocket(port);
    static std::vector<Client*> clients;

    ////////////////////////////
    // Static functions prototypes

    static void host();
    static void create_client(const ClientSocket& clientSocket);
    static void remove_client(const Client* pClient);

    ////////////////////////////
    // External functions definitions

    void Server::run()
    {
        serverSocket.server_winsock2_startup();
        serverSocket.server_open_socket();
        serverSocket.server_bind();
        serverSocket.server_listen(maxClients);

        std::thread thread(host);
        thread.detach();
    }

    void Server::close()
    {
        // Durak class has the responsibility to disconnect the connected players.
        // This responsibility doesn't include closing the sockets tho.
        isOpen = false;
        for (auto pClient : clients)
        {
            remove_client(pClient);
        }
        serverSocket.server_close();
        tcout << T("Server is dead!") << endl;
    }

    bool Server::is_open()
    {
        return isOpen;
    }

    ////////////////////////////
    // Static functions definitions

    void host()
    {
        tcout << T("Server is running on port ") << port << T("!") << endl;
        isOpen = true;

        while (true)
        {
            try
            {
                std::thread thread(create_client, serverSocket.server_accept());
                thread.detach();
            }
            catch (const std::exception& ex) // Should be thrown when the server shuts down!
            {
                // Relevant only if the server is still open!
                if (isOpen)
                {
                    std::cout << ex.what() << endl;
                }
            }
        }
    }

    void create_client(const ClientSocket& clientSocket)
    {
        tcout << T("Handshake from ") << clientSocket.address << T(":") << clientSocket.port << endl;

        constexpr long timeoutMillis = 1500; // half a second to send the first packet
        clientSocket.client_set_timeout(timeoutMillis);

        // Copy the magic entry packet to an array
        char magicEntryPacketArray[sizeof(magicEntryPacket)]; 
        memcpy(magicEntryPacketArray, &magicEntryPacket, sizeof(magicEntryPacket));

        bool success = false;

        char buffer[sizeof(magicEntryPacketArray)];
        // Make sure that the socket has read the currect amount of bytes
        if (clientSocket.client_recv(buffer, sizeof(buffer)) == sizeof(buffer))
        {
            if (!memcmp(buffer, magicEntryPacketArray, sizeof(buffer)))
            {
                success = true;
            }
        }

        if (!success)
        {  
            tcout << clientSocket.address << T(":") << clientSocket.port <<
                T(" has failed to send the magic entry packet in ") <<
                timeoutMillis << T("ms!") << endl;

            clientSocket.client_close();
        }
        else
        {
            // Create the client, run it, and then close it
            // The client will loop on the same thread
            auto pClient = new Client(clientSocket);
            clients.push_back(pClient);

            pClient->run();
            
            // Super important:
            // TODO: Notify the game that the player has disconnected before removing his client!
            
            // Important!
            // When the server is closed, first this flag is set to false,
            // and only then removes the clients
            // Because the threads are racing, this flag must be checked
            if (isOpen)
            {
                remove_client(pClient);
            }
        }

        return;
    }

    void remove_client(const Client* pClient)
    {
        auto& v = clients;

        v.erase(std::remove(v.begin(), v.end(), pClient));
        delete pClient;
    }
} // namespace Network
