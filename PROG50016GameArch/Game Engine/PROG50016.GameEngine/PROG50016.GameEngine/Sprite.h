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

protected:

    /***** Functions *****/

    void render() override;

public:

    Sprite();

    ~Sprite();

    void update() override;

    std::string getComponentId();
};

#endif
