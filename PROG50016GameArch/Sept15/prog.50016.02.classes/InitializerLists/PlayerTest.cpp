#include "Player.h"
#include <iostream>

int main()
{
    Player p("Jim", 3, 100.0f, 100.0f);

    std::cout << p.getName() << " has " << p.getNumLives() << " lives and " << p.getHealth() << " health" << std::endl;
}
