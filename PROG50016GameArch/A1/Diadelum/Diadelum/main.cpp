
#include <iostream>

#include "GameEngine.h"


int main(int argc, const char *argv[]) {

    GameEngine engine;
    std::string s = "";

    engine.initialize(s);
    engine.gameLoop();

    return -1;
}