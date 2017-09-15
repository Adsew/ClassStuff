#include "Monster.h"
#include "Point.h"
#include <iostream>

int main()
{
	Point p1;
	Point p2;

	float distance = Point::calculateDistance(p1, p2);

    Monster bob("BadassBob");

    bob.applyDamage(15);

    // compute health percentage
    // - note the different way of calling instance and static methods
    float healthPercentage = 100 * bob.getHealth() / Monster::getMaxHealth();

    std::cout << bob.getName() << "'s health is at " << healthPercentage << "%" << std::endl;
}
