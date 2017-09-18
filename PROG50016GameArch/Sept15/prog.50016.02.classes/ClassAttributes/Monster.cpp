#include "Monster.h"

// Declare storage for the static attributes.
// - NOTE 1: this must be done in a source file, not the header!
// - NOTE 2: do not use the 'static' keyword here!
// - NOTE 3: use the fully qualified name (Class::Attribute)
// - NOTE 4: don't forget to intialize here, since there are no "static constructors"!

float Monster::smMaxHealth = 0;

// a constructor
Monster::Monster(std::string name)
{
    mName = name;
    mHealth = smMaxHealth;  // use static attribute from this class
}

// instance method
std::string Monster::getName() const
{
    return mName;
}

// instance method
float Monster::getHealth() const
{
    return mHealth;
}

// instance method
void Monster::applyDamage(float damageAmount)
{
    mHealth -= damageAmount;
}

float Monster::getMaxHealth() {

    return smMaxHealth;
}
