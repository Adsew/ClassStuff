/*
Student: James Brooks
Class: Game Architecture

File: ButtonActionQuit.cpp

Class: ButtonActionQuit

Description: Button action that quits the game on click
*/


#include "Core.h"

#include "InputManager.h"
#include "ButtonActionQuit.h"


IMPLEMENT_COMPONENT(ButtonActionQuit);


ButtonActionQuit::ButtonActionQuit(unsigned int uniqueID)
    : ButtonAction(uniqueID, "ButtonActionQuit") {

    
}

ButtonActionQuit::ButtonActionQuit(unsigned int uniqueID, const char *type)
    : ButtonAction(uniqueID, type) {

    
}

ButtonActionQuit::~ButtonActionQuit() {


}

void ButtonActionQuit::onClick() {

    InputManager::Instance().exit();
}
