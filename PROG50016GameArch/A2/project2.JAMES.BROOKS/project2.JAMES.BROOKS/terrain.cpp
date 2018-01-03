/*
Student: James Brooks
Class: Game Architecture

File: Terrain.cpp

Class: Terrain

Description: Keeps track of map data for the current level.
*/


#include "Core.h"

#include "Sprite.h"
#include "terrain.h"


IMPLEMENT_COMPONENT(Terrain);


Terrain::Terrain(unsigned int uniqueID)
    : Component(uniqueID, "Terrain") {


}

Terrain::Terrain(unsigned int uniqueID, const char *compType)
    : Component(uniqueID, compType) {


}


Terrain::~Terrain() {

    unloadTiles();
}

void Terrain::initialize() {


}

void Terrain::update() {


}

void Terrain::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string mapFile = "";

    if (FileSystem::Instance().getAttribute(accessor, "mapefile", mapFile)) {

        loadMapFile(mapFile.c_str());
    }
}

// Unload tiles held by the map, if any
void Terrain::unloadTiles() {

    for (int i = 0; i < terrain.size(); i++) {
        for (int j = 0; j < terrain[i].size(); j++) {

            if (terrain[i][j] != NULL) {

                terrain[i][j]->destroy();
            }
        }

        terrain[i].clear();
    }

    terrain.clear();

    for (int i = 0; i < objects.size(); i++) {
        for (int j = 0; j < objects[i].size(); j++) {

            if (objects[i][j] != NULL) {

                objects[i][j]->destroy();
            }
        }

        objects[i].clear();
    }

    objects.clear();
}

// Load a map file and create the tiles needed
void Terrain::loadMapFile(const char *mapFile) {

    std::unique_ptr<FileSystem::FileAccessor> mapFileAccessor = FileSystem::Instance().loadFile(mapFile, mapFile);

    if (mapFileAccessor != NULL) {

        unloadTiles();

        if (FileSystem::Instance().traverseToElement(mapFileAccessor, "map")) {

            int width = 0, height = 0;

            FileSystem::Instance().getAttribute(mapFileAccessor, "width", width);
            FileSystem::Instance().getAttribute(mapFileAccessor, "height", height);

            // Load underlying terrain such as the grass
            if (FileSystem::Instance().traverseToElement(mapFileAccessor, "layer")) {

                std::string data = "";

                FileSystem::Instance().traverseToElement(mapFileAccessor, "data");

                FileSystem::Instance().getElementText(mapFileAccessor, data);

                terrain.resize(height);

                for (int i = 0; i < terrain.size(); i++) {

                    terrain[i].resize(width);

                    for (int j = 0; j < terrain[i].size(); j++) {

                        // get data, create tile and 
                    }
                }

                FileSystem::Instance().traverseToParentElement(mapFileAccessor);
            }

            // load the objects in now
            if (FileSystem::Instance().traverseToSyblingElement(mapFileAccessor)) {

                std::string data = "";

                FileSystem::Instance().traverseToElement(mapFileAccessor, "data");

                FileSystem::Instance().getElementText(mapFileAccessor, data);

                objects.resize(height);

                for (int i = 0; i < objects.size(); i++) {

                    objects[i].resize(width);

                    for (int j = 0; j < objects[i].size(); j++) {

                        // get data create tiles and stuff
                    }
                }

                FileSystem::Instance().traverseToParentElement(mapFileAccessor);
            }
        }
    }
}
