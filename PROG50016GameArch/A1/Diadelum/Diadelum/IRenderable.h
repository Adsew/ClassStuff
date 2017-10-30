#ifndef IRENDERABLE_H
#define IRENDERABLE_H

/*
Student: James Brooks
Class: Game Architecture

File: IRenderable.h

Class: IRenderable

Description: An interface to be added to game objects allowing them to be rendered to the screen
    by the RenderSystem class.
*/


class IRenderable {
    friend class RenderSystem;

protected:

    /***** Functions *****/

    virtual void render() = 0;
};

#endif
