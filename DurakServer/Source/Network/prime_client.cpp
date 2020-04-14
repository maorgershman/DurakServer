#include <Network/prime_client.hpp>
#include <Network/player_client.hpp>

namespace Network
{
    PrimeClient::PrimeClient(ClientSocket&& socket)
        : socket(socket)
    {
        tcout << T("Handshake from ") << to_string() << endl;

        // Hard coded values that should be sent in the first packet to indicate the client's intent
        constexpr auto magicCode_Player = 0xace0beef;
        constexpr auto magicCode_Spectator = 0x00f1dead;

        // The time, in milliseconds, that the packet can be received before timing out
        constexpr long packetTimeoutMillis = 1500;

        char magicPacketArray_Player[sizeof(magicCode_Player)];
        char magicPacketArray_Spectator[sizeof(magicCode_Spectator)];
        char packetBuffer[max(sizeof(magicCode_Player), sizeof(magicCode_Spectator))];

        socket.client_set_timeout(packetTimeoutMillis);
        memcpy(magicPacketArray_Player, &magicCode_Player, sizeof(magicPacketArray_Player));
        memcpy(magicPacketArray_Spectator, &magicCode_Spectator, sizeof(magicPacketArray_Spectator));

        int bytesRead = socket.client_recv(packetBuffer, sizeof(packetBuffer));
        if (bytesRead == sizeof(magicCode_Player) || bytesRead == sizeof(magicCode_Spectator))
        {
            if (!memcmp(packetBuffer, magicPacketArray_Player, bytesRead))
            { // Is player
                // Create a player client
                PlayerClient playerClient(*this);
            }
            else if (!memcmp(packetBuffer, magicPacketArray_Spectator, bytesRead))
            { // Is spectator
                // TODO: Create a spectator client
            }
            else
            { // Invalid response or timed out
                tcout << to_string() << T(" has failed to identify in ") << packetTimeoutMillis << T("ms!") << endl;
            }
        }
    }

    PrimeClient::~PrimeClient()
    {
        socket.client_close();
    }

    const tstring PrimeClient::to_string() const
    {
        return socket.to_string();
    }
} // namespace Network
