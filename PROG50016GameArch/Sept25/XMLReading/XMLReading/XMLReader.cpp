/*
File: XMLReader.cpp

Description: Reads XML files and simply displays the data
*/


#include <iostream>

#include "tinyxml2.h"


using namespace tinyxml2;


int loadXMLSettings() {

    XMLDocument *doc = new XMLDocument();

    if (doc->LoadFile("XMLReading/GameSettings.xml")) {

        XMLNode *settings = doc->FirstChildElement("GameSettings");

        if (settings != NULL) {

            XMLElement *gameName = settings->FirstChildElement("Name");

            std::cout << gameName->GetText();
        }
    }

    return 0;
}

int main() {

    loadXMLSettings();

    //loadXMLLevel();

    //loadXMLLevelExample();

    return -1;
}