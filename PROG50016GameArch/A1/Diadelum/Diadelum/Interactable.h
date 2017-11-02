#ifndef INTERACTABLE_H
#define INTERACTABLE_H

/*
Student: James Brooks
Class: Game Architecture

File: Interactable.h

Class: Interactable

Description: Represents something in the environment that can be
    interacted with.
*/


#include "GameObject.h"


class Interactable : public GameObject {

public:

    /***** functions *****/

    Interactable(int idNum, std::string);

    virtual ~Interactable();

        // Interactivity functions

    std::string use();

    std::string useWith(GameObject *go);

    std::string lookat();
};

#endif
