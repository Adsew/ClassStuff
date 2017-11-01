#ifndef I_RENDERABLE_H
#define I_RENDERABLE_H

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

    virtual std::string render() = 0;
};

#endif
