

#include "../NetworkCommon.h"

#include <iostream>
#include <string>

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakSleep.h>

int main() {

    // Get unique instance
    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd(SERVER_PORT, 0);

    // First val is num of people who can connect, you can pass a c-array of SDs, third arg is how many SDs passed
    RakNet::StartupResult startCode = peer->Startup(25, &sd, 1);

    if (startCode == RakNet::RAKNET_STARTED) {
        std::cout << "Server started" << std::endl;
    }
    else {
        std::cerr << "Error on startup. Error code: " << startCode << std::endl;
        RakNet::RakPeerInterface::DestroyInstance(peer);
        return -1;
    }
    //Make sure we are allowing incoming connections.
    peer->SetMaximumIncomingConnections(30);

    while (true) {
        RakNet::Packet *packet = peer->Receive();
        while (packet != NULL) {
            switch (packet->data[0]) {
            case ID_NEW_INCOMING_CONNECTION:
                //New Connection.
                std::cout << "New connection from peer " +
                    std::string(packet->systemAddress.ToString(true)) << std::endl;
                break;
            case MSG_CHAT_PACKET:
            {
                char const *msg = (char const *)packet->data + 1;
                std::cout << msg << std::endl;
            }
            peer->Send((char const *)packet->data, packet->length,
                HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                packet->systemAddress, true);   // Send and rebroadcast to all but who sent it
            break;
            default:
                //Everything else
                std::cout << "Unhandled packet type from peer " +
                    std::string(packet->systemAddress.ToString(true)) << std::endl;
                break;
            }

            //When we are done, deallocate the packet and
            // check if there is another.
            peer->DeallocatePacket(packet);
            packet = peer->Receive();
        } //while( packet != NULL)

        RakSleep(10);
    }

    RakNet::RakPeerInterface::DestroyInstance(peer);

    std::cout << "Server shutting down." << std::endl;

    return 0;
}