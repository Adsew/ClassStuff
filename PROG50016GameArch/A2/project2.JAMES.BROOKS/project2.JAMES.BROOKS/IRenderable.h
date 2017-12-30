#ifndef I_RENDERABLE_H
#define I_RENDERABLE_H

/*
Student: James Brooks
Class: Game Architecture

File: IRenderable.h

Class: IRenderable

Description: Interface to provide screen rendering functionality.
*/


class IRenderable {

	friend class RenderSystem;

protected:	
	
    IRenderable();

    virtual ~IRenderable();

    // Called to render the object to the window
	virtual void render() = 0;
};

#endif // !I_RENDERABLE_H
