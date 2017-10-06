#ifndef ISYSTEM_H
#define ISYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: ISystem.h

Class: ISystem

Description:
*/


class ISystem {

public:

    /***** Functions *****/

    virtual int priority() = 0;

    virtual void update() = 0;
};

#endif
