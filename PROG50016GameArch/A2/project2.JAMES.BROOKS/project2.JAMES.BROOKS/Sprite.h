#ifndef SPRITE_H
#define SPRITE_H

/*
Student: James Brooks
Class: Game Architecture

File: Sprite.h

Class: Sprite

Description: A small image to be rendered to the screen.
*/


#include "Component.h"
#include "IRenderable.h"


class TextureAsset;


class Sprite : public Component, public IRenderable {

    REGISTER_COMPONENT(Sprite)                                                  

protected:

    std::weak_ptr<TextureAsset> spriteImage;

    // Image rendering
    int xDimension, yDimension;
    int xOrigin, yOrigin;

    // Render screen position
    int xPos, yPos;

    /***** Functions *****/

protected:

    virtual void render() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

	Sprite(unsigned int uniqueID);

	virtual ~Sprite();
	
	virtual void initialize() override;

    virtual void update() override;
};

#endif // !SPRITE_H
