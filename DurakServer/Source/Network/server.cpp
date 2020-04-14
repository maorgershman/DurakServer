#include <Network/server_socket.hpp>
#include <Network/prime_client.hpp>

#include <thread>

namespace Network
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
    // External functions definitions

    void Server::run()
    {
        serverSocket.server_winsock2_startup();
        serverSocket.server_open_socket();
        serverSocket.server_bind();
        serverSocket.server_listen(maxClients);

        std::thread thread(
            [&]()
            {
                tcout << T("Server is running on port ") << port << T("!") << endl;
                isOpen = true;

                while (isOpen)
                {
                    try
                    {
                        std::thread thread(
                            [&](ClientSocket&& clientSocket)
                            {
                                // Accept a prime, mid-level client that will abstract the client socket.
                                // It will be allocated on the stack and pause the thread.
                                // The destructor will release resources

                                PrimeClient client(std::move(clientSocket));
                            }, serverSocket.server_accept());
                        thread.detach();
                    }
                    catch (const std::exception& ex)
                    {
                        if (isOpen)
                        { // When closing the socket, an exception will be thrown (naturally). Ignore it
                            std::cout << ex.what() << endl;
                        }
                    }
                }
            });
        thread.detach();
    }

    void Server::close()
    {
        isOpen = false;
        serverSocket.server_close();
        tcout << T("Server is dead!") << endl;
    }
} // namespace Network
