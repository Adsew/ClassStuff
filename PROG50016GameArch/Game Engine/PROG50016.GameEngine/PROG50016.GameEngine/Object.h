#ifndef OBJECT_H
#define OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: Object.h

Class: Object

Description: Base class for all objects in the game engine
*/


#include <string>
#include <list>


class Object {

private:

    /***** Variables *****/

    std::string name;

    bool initialized;


public:

    /***** Functions *****/

    Object();

    virtual ~Object();

    // Check object initialized correctly and ise usable
    bool isInitialized();

    // Get name of object
    std::string getName();

    // Initialize object to a usable state
    virtual void initialize();

    // Display object to the screen
    void display();
};

#endif
