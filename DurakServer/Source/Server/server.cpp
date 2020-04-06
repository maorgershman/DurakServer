#include <Server/server_socket.hpp>

#include <thread>

namespace Server
{
    ////////////////////////////
    // Static constant variables

    static constexpr int maxClients = 6;
    static constexpr int port = 8888;

    ////////////////////////////
    // Static variables

    static bool isOpen = false;
    static ServerSocket serverSocket(port);

    ////////////////////////////
    // Static functions prototypes

    static void host();
    static void create_client(const ClientSocket& clientSocket);

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
        // The server should only handle technical sockety stuff.
        isOpen = false;
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

        // TODO: Actually accept a player. 
        // Durak class should handle the players, the server is only an interface.
    }
} // namespace Server
