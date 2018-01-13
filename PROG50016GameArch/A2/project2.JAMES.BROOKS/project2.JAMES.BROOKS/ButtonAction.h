#ifndef BUTTON_ACTION_H
#define BUTTON_ACTION_H

/*
Student: James Brooks
Class: Game Architecture

File: ButtonAction.h

Class: ButtonAction

Description: Base class for a button action that will be set to a button to make it work
*/


#include "Component.h"


class ButtonAction : public Component {

    /***** Variables *****/

protected:

    bool functionSet;


    /***** Functions *****/

protected:

    ButtonAction(unsigned int uniqueID, const char *type);

    ~ButtonAction();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    virtual void onClick() = 0;
};

#endif // !BUTON_ACTION_H
