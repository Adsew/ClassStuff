
#include "RakNetClient.h"


#include <Windows.h>

#include <iostream>
#include <string>

#include "SFML/Window.hpp"


int main(int argc, char **argv) {
    
    RakNetClient client;
    
    std::string IPaddress = "";
    unsigned int port = 1288;

    std::cout << "Enter the IP address followed by port number. Eg: 127.0.0.1 1288" << std::endl;
    std::cin >> IPaddress >> port;

    client.Start();
    client.Connect(port, IPaddress.c_str());

    if (client.Connect(port, IPaddress.c_str())) {

        sf::Window window(sf::VideoMode(800, 600), "Group Draw");

        Sleep(2000);
    }

    client.Disconnect(true);
    client.Shutdown(true);
    //Make sure the server block duration is allowed to run to completion.
    Sleep(1500);

}