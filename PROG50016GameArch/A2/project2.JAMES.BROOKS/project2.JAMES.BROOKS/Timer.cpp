/*
Student: James Brooks
Class: Game Architecture

File: Timer.cpp

Class: Timer

Description: Class to manage time of the game during execution, in delta time
    per update and total play time. Named Timer only to avoid potential conflict
    with anything native named Time.
*/


#include "Core.h"

#include "Timer.h"


void Timer::initialize() {

    runTime = 0.0f;
    deltaTime = 0.0f;
}

void Timer::update() {

    prevClockTime = clock() - prevClockTime;
    deltaTime = ((float)prevClockTime) / ((clock_t)1000);
    runTime += deltaTime;

    prevClockTime = clock();
}

void Timer::beginTiming() {

    prevClockTime = clock();
}

// Return the delta time of the previous update
float Timer::getDelta() {

    return deltaTime;
}

// Return the current total game runtime since after initialization
float Timer::getRuntime() {

    return runTime;
}
