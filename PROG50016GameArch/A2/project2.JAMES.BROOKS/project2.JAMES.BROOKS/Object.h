#ifndef OBJECT_H
#define OBJECT_H

/*
Student: James Brooks
Class: Game Architecture

File: Object.h

Class: Object

Description: Base class for most entities persisting in the game world.
*/


class Object {


    /**** Variables *****/

private:
	
    unsigned int id;

    bool initialized;
    bool needsDeletion;


    /***** Functions *****/

protected:
	
    Object(unsigned int uniqueID);

    virtual ~Object();
	
public:

    // Return true if id's are the same
    bool operator==(const Object &obj);

    // Initialize object to a usable state
	virtual void initialize() = 0;

    // Return true if object has been initialized
    bool isInitialized();

    // Set an object to be deleted by the manager
    void destroy();

    // Check if object is set for deletion
    bool pollNeedsDeletion();
};

#endif // !OBJECT_H
