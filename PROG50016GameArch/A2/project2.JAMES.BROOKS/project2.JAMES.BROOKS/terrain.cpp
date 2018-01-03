/*
Student: James Brooks
Class: Game Architecture

File: Terrain.cpp

Class: Terrain

Description: Keeps track of map data for the current level.
*/


#include "Core.h"

#include <sstream>

#include "GameObjectManager.h"
#include "Tile.h"
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

// Create a tile gameobject with the given properties
GameObject *createTile(const char *tileAssetName, int w, int h, int xOrig, int yOrig, int xPos, int yPos, bool collider) {


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

            std::string tileset = "";
            int tilesAcross = 0, tilesDown = 0, tileWidth = 0, tileHeight = 0;
            int mapWidth = 0, mapHeight = 0;

            FileSystem::Instance().getAttribute(mapFileAccessor, "width", mapWidth);
            FileSystem::Instance().getAttribute(mapFileAccessor, "height", mapHeight);

            FileSystem::Instance().getAttribute(mapFileAccessor, "tilewidth", tileWidth);
            FileSystem::Instance().getAttribute(mapFileAccessor, "tileheight", tileHeight);

            // Get tileset data
            if (FileSystem::Instance().traverseToElement(mapFileAccessor, "tileset")) {

                FileSystem::Instance().getAttribute(mapFileAccessor, "texture", tileset);
                FileSystem::Instance().getAttribute(mapFileAccessor, "width", tilesAcross);
                FileSystem::Instance().getAttribute(mapFileAccessor, "height", tilesDown);
            }

            // Load underlying terrain such as the grass
            if (FileSystem::Instance().traverseToSyblingElement(mapFileAccessor, "layer")) {

                std::string data = "";

                FileSystem::Instance().traverseToElement(mapFileAccessor, "data");

                FileSystem::Instance().getElementText(mapFileAccessor, data);

                std::stringstream dataStream(data);

                // Iterate and fill map with tiles based on data
                terrain.resize(mapHeight);

                for (int i = 0; i < terrain.size(); i++) {

                    terrain[i].resize(mapWidth);

                    for (int j = 0; j < terrain[i].size(); j++) {

                        int x = 0, y = 0, tileNum = 0;

                        dataStream >> tileNum;

                        if (tileNum != 0) {

                            tileNum--;
                            x = (tileNum % tilesAcross) * tileHeight;
                            y = ((int)(tileNum / tilesDown)) * tileWidth;

                            terrain[i][j] = createTile(tileset.c_str(), tileWidth, tileHeight, x, y, i, j, false);
                        }
                        else {

                            terrain[i][j] = NULL;
                        }
                    }
                }

                FileSystem::Instance().traverseToParentElement(mapFileAccessor);
            }

            // load the objects in now
            if (FileSystem::Instance().traverseToSyblingElement(mapFileAccessor)) {

                std::string data = "";

                FileSystem::Instance().traverseToElement(mapFileAccessor, "data");

                FileSystem::Instance().getElementText(mapFileAccessor, data);

                std::stringstream dataStream(data);

                // Iterate and fill map with tiles based on data
                objects.resize(mapHeight);

                for (int i = 0; i < objects.size(); i++) {

                    objects[i].resize(mapWidth);

                    for (int j = 0; j < objects[i].size(); j++) {

                        int x = 0, y = 0, tileNum = 0;

                        dataStream >> tileNum;

                        if (!0) {

                            tileNum--;
                            x = (tileNum % tilesAcross) * tileHeight;
                            y = ((int)(tileNum / tilesDown)) * tileWidth;

                            objects[i][j] = createTile(tileset.c_str(), tileWidth, tileHeight, x, y, i, j, false);
                        }
                        else {

                            objects[i][j] = NULL;
                        }
                    }
                }

                FileSystem::Instance().traverseToParentElement(mapFileAccessor);
            }
        }
    }
}
