/*
Student: James Brooks
Class: Game Architecture

File: main.cpp

Description: Runs the tests required to show everything initialized properly.
*/


#include "GameEngine.h"


int main(int argc, const char *argv[]) {

    GameEngine myGE;
    std::string fileLoc = "../Res/GameSettings.xml";

    myGE.initialize(fileLoc);
    
    myGE.gameLoop();

    myGE.display();

    return -1;
}