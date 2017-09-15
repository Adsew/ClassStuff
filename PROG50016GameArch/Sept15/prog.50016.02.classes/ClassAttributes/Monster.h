#ifndef MONSTER_H__
#define MONSTER_H__

#include <string>

class Monster 
{

    static float smMaxHealth;  // maximum amount of health any monster could have (class attribute)

    std::string mName;      // the name of this monster (instance attribute)
    float mHealth;            // the amount of health a monster has (instance attribute)

public:
    // a constructor
    Monster(std::string name);

    // instance methods
    std::string getName() const;
    float getHealth() const;
    void applyDamage(float damageAmount);

    // static methods
    static float getMaxHealth();
};

#endif
