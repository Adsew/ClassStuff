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


class Object {

private:

    /***** Variables *****/

    bool initialized;

protected:

    std::string name;

public:

    /***** Functions *****/

    Object();

    Object(std::string &n);
    
    virtual ~Object();

    // Initialize object to a usable state
    virtual void initialize();

    // Check object initialized correctly and ise usable
    bool isInitialized();

    // Cycle update for object
    virtual void update() = 0;

    // Get name of object
    std::string &getName();
};

#endif
