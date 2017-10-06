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
#include "IRenderable.h"


class Sprite : public Component, public IRenderable {

public:

    /***** Functions *****/

    Sprite();

    ~Sprite();

    void update() override;

    void render() override;

    std::string getComponentId();
};

#endif
