#ifndef PLAYER_H__
#define PLAYER_H__

#include <string>

#include "Point.h"

class Player 
{

    std::string mName;
    int mNumLives;
    float mHealth;
	const float mMaxHealth;
	Point mPosition;

public:
	Player()
	{
	}

    //
    // a constructor that uses an initializer list
    //
    Player(std::string name, int numLives, float health, float maxHealth)
    {
    }

    std::string getName() const		{ return mName; }
    int getNumLives() const			{ return mNumLives; }
    float getHealth() const			{ return mHealth; }
};

#endif
