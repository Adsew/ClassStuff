#pragma once

/*
File: ShaderLoader.h

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Class: ShaderLoader

Description: Class responsible for loadinga shader file and
converting it into a usable string.
*/


#include <string>


class ShaderLoader {

private:

    /***** Variables *****/

    std::string fileTxt;

public:

    /***** Functions *****/

    /* Loads file from given location */
    ShaderLoader(std::string &filLoc);

    /* Retrieve loaded text, if any. Return \0 on error */
    std::string getText();
};