#ifndef I_RENDERABLE_H
#define I_RENDERABLE_H

/*
Student: James Brooks
Class: Game Architecture

File: IRenderable.h

Class: IRenderable

Description: Interface to provide screen rendering functionality.
*/


#define HIGHEST_PRIORITY 0
#define HIGH_PRIORITY 1
#define MID_PRIORITY 2
#define LOW_PRIORITY 3
#define LOWEST_PRIORITY 4

#define PRIORITIES 5


class IRenderable {

	friend class RenderSystem;

    /***** Variables *****/

private:

    unsigned int priority;


    /***** Functions *****/

protected:	
	
    IRenderable(unsigned int p);

    virtual ~IRenderable();

    // Called to render the object to the window
	virtual void render() = 0;

public:

    // Set the priority the object will render over others
    void setRenderPriority(unsigned int p);
};

#endif // !I_RENDERABLE_H
