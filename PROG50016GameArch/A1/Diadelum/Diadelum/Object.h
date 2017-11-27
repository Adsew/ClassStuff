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
    bool needsDeletion;

protected:

    std::string name;

public:

    /***** Functions *****/

    Object();

    Object(const char *n);

    Object(std::string &n);
    
    virtual ~Object();

    // Initialize object to a usable state
    virtual void initialize();

    // Check object initialized correctly and ise usable
    bool isInitialized();

    // Cycle update for object
    virtual void update() = 0;

    // Set object for deletion at a later time by manager
    void destroy();

    // Returns the status of the object if it is to be destroyed
    bool getNeedsDeletion();

    // Get name of object
    std::string &getName();
};

#endif
