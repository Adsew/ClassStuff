#ifndef ZONE_H
#define ZONE_H

/*
Student: James Brooks
Class: Game Architecture

File: Zone.h

Class: Zone

Description: Holds all information and can be interacted with for
    any zone. Information contained is generally dynamic depending
    on the zone's specific details.
*/


#include "IRenderable.h"
#include "Object.h"


class Zone : public Object, public IRenderable {

public:

    Zone();

    ~Zone();

    // POut use move etc functions here and a general determine function
    // that will use the array t o determine which pointer function to use
    // Initialize will set up the function pointers
};

#endif
