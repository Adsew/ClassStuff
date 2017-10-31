/*
Student: James Brooks
Class: Game Architecture

File: main.cpp

Description: main code file to begine the engine running.
*/


#include "GameEngine.h"


int main(int argc, const char *argv[]) {

    GameEngine engine;
    std::string s = "";

    engine.initialize(s);
    engine.gameLoop();

    return -1;
}
