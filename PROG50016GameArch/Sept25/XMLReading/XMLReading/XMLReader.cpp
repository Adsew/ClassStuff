/*
File: XMLReader.cpp

Description: Reads XML files and simply displays the data
*/


#include <iostream>

#include "tinyxml2.h"


using namespace tinyxml2;


int loadXMLLevel() {

    XMLDocument doc;

    doc.LoadFile("../Res/GameLevel.xml");

    if (doc.Error() == false) {

        XMLNode *level = doc.FirstChildElement("Level");
        
        if (level != NULL) {

            XMLElement *firstActor = level->FirstChildElement("Actor"); // Get next sybling using that pointer to get all actors

            XMLElement *secondActor = firstActor->NextSibling;

            if (firstActor != NULL) {

                //Actor act = new Actor(firstActor);    // Now we let the class handle its own loading, it should know what it needs

                // In calss do same thing get elements of name, rotation, position, etc till all wanted data is loaded.
                // Dont always have to get everything, can check for null if null set a default, if not use the data, 
                // this saves memory when saving dont always need to write variables
                // Elements are like variables and classes tp match your actual code classes
            }
        }
    }

    return 0;
}

int main() {

    //loadXMLSettings();

    loadXMLLevel();

    //loadXMLLevelExample();

    return -1;
}