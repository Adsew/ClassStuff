#ifndef TIMER_H
#define TIMER_H

/*
Student: James Brooks
Class: Game Architecture

File: Timer.h

Class: Timer

Description: Class to manage time of the game during execution, in delta time
    per update and total play time. Named Timer only to avoid potential conflict
    with anything native named Time.
*/


#include <time.h>

#include "ISystem.h"


class Timer : public ISystem {

    friend class GameEngine;


    /***** Variables *****/

private:

    clock_t prevClockTime;

    float runTime;

    float deltaTime;


    /***** Functions *****/

private:

    Timer() = default;

    Timer(const Timer& other) = default;

    ~Timer() = default;

protected:

    void initialize() override;

    void update() override;

    void beginTiming();

public:

    inline static Timer &Instance() {

        static Timer instance;

        return instance;
    }

    // Return the delta time of the previous update
    float getDelta();

    // Return the current total game runtime since after initialization
    float getRuntime();
};

#endif // !TIMER_H
