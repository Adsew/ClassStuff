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


class Sprite : public Component, public IRenderable {

public:

	Sprite();

	~Sprite();
	
	virtual void initialize() override;
	
	std::string getComponentId() override { return "Sprite"; }

protected:	
	
	virtual void render() override;
};

#endif // !SPRITE_H
