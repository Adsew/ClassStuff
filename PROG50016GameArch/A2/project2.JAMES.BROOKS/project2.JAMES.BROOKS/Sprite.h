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

    /***** Type Creator *****/

private:

    static void generateType();

    class TypeRegister {

        static bool dummy;

        TypeRegister() {

            REGISTER_COMPONENT(Sprite)
        }

        ~TypeRegister() = default;
    };

    /***** Functions *****/

protected:

    virtual void render() override;

public:

	Sprite(unsigned int uniqueID);

	virtual ~Sprite();
	
	virtual void initialize() override;

    virtual void update() override;
};

#endif // !SPRITE_H
