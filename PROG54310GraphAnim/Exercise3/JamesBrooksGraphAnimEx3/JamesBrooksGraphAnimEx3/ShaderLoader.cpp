/*
File: ShaderLoader.cpp

Student: James Brooks
Assignment: Graphics and Animation Exercise 2

Class: ShaderLoader

Description: Class responsible for loading a shader file and
    converting it into a usable string.
*/


#include <iostream>
#include <fstream>

#include "ShaderLoader.h"


    /* Constructor */

ShaderLoader::ShaderLoader(std::string &fileLoc) {

    std::ifstream inStream(fileLoc, std::ios::in);

    fileTxt = "";

    if (inStream.is_open()) {

        std::string line = "";

        while (getline(inStream, line)) {

            fileTxt = fileTxt + line + "\n";
        }
        
        inStream.close();
    }
    else {

        std::cerr << "Could not open file " << fileLoc << ". File not found.\n";

        fileTxt = "\0";
    }
}

    /* Support Functions */

std::string ShaderLoader::getText() {

    return fileTxt;
}
