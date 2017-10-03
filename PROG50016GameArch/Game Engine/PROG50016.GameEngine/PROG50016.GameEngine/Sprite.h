#ifndef SPRITE_H
#define SPRITE_H

/*
Student: James Brooks
Class: Game Architecture

File: Sprite.h

Class: Sprite

Description:
*/


#include "Component.h"


class Sprite : public Component {

public:

    /***** Functions *****/

    Sprite();

    ~Sprite();

    std::string getComponentId() { return "Sprite";  }
};

#endif
