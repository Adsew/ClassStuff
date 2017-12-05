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

private:
	
    bool initialized;
	
    std::string name;

public:
	
    int something;

public:
	
    Object();
	
    virtual ~Object();

	virtual void initialize();

	bool isInitialized() { return initialized; }
	
    std::string getName() { return name; }
};

#endif // !OBJECT_H
