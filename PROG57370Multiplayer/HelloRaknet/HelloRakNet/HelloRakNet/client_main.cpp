
#include "../NetworkCommon.h"

#include <iostream>
#include <string>

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakSleep.h>
#include <Kbhit.h>

int main() {

    std::cout << "Starting client." << std::endl;

    // Get unique instance
    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

    RakNet::SocketDescriptor sd;    // Port doesnt matter on our machine, use any

    // First val is num of people who can connect, you can pass a c-array of SDs, third arg is how many SDs passed
    RakNet::StartupResult startCode = peer->Startup(1, &sd, 1);

    if (startCode == RakNet::RAKNET_STARTED) {

        std::cout << "Client is running." << std::endl;
    }
    else {

        std::cout << "Error running client." << std::endl;
        RakNet::RakPeerInterface::DestroyInstance(peer);

        return 1;
    }

    // Dont have a password
    peer->Connect("127.0.0.1", SERVER_PORT, NULL, 0);
    RakNet::SystemAddress address;

    while (true) {
        RakNet::Packet *packet = peer->Receive();
        while (packet != NULL) {
            switch (packet->data[0]) {
            case ID_CONNECTION_REQUEST_ACCEPTED:
                //New Connection.
                std::cout << "Connection accepted by peer at " +
                    std::string(packet->systemAddress.ToString(true)) << std::endl;
                address = packet->systemAddress;
                break;
            case MSG_CHAT_PACKET: {
                char const *msg = (char const *)packet->data + 1;
                std::cout << msg << std::endl;
            }
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

        if (_kbhit()) {
            std::string message;
            std::getline(std::cin, message);
            int len = 1 + message.size() + 1; //ID + length of message + NULL terminator.
            char *msg = new char[len];
            msg[0] = (unsigned char)MSG_CHAT_PACKET;
            strcpy_s(msg + 1, len-1, message.c_str());

            peer->Send(msg, len, HIGH_PRIORITY, RELIABLE_ORDERED, 0, address, false);

            delete[] msg;
        }

        RakSleep(10);

    }

    return 0;
}