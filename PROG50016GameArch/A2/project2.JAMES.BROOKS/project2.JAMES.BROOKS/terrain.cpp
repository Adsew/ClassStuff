/*
Student: James Brooks
Class: Game Architecture

File: Terrain.cpp

Class: Terrain

Description: Keeps track of map data for the current level.
*/


#include "Core.h"

#include <sstream>

#include "ComponentManager.h"
#include "GameObjectManager.h"
#include "Tile.h"
#include "Sprite.h"
#include "Transform.h"
#include "terrain.h"


#define SPAWN_POINT_ID 15


IMPLEMENT_COMPONENT(Terrain);


Terrain::Terrain(unsigned int uniqueID)
    : Component(uniqueID, "Terrain") {

    tileWidth = 0;
    tileHeight = 0;
}

Terrain::Terrain(unsigned int uniqueID, const char *compType)
    : Component(uniqueID, compType) {

    tileWidth = 0;
    tileHeight = 0;
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

    if (FileSystem::Instance().getAttribute(accessor, "mapfile", mapFile)) {

        loadMapFile(mapFile.c_str());
    }
}

// Create a tile gameobject with the given properties
GameObject *Terrain::createTile(const char *tileAssetName, int w, int h, int xOrig, int yOrig, int xPos, int yPos, bool collider, unsigned int renderPriority) {

    GameObject *tile = GameObjectManager::Instance().createGameObject();
    Tile *tileComp = (Tile *)ComponentManager::Instance().createComponent("Tile");
    Sprite *tileSprite = (Sprite *)ComponentManager::Instance().createComponent("Sprite");
    Transform *tileTrans = tile->getTransform();

    tile->setName("Tile");
    tile->setScene(this->gameObject);

    tileComp->setCollidable(collider);

    tileSprite->setRectangle(w, h, xOrig, yOrig);
    tileSprite->setTextureAsset(tileAssetName);
    tileSprite->setRenderPriority(renderPriority);

    tileTrans->setPosition((float)xPos, (float)yPos);

    tile->addComponent(tileComp);
    tile->addComponent(tileSprite);

    return tile;
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

Component &Terrain::operator=(const Component &comp) {

    return *this;
}

// Load a map file and create the tiles needed
void Terrain::loadMapFile(const char *mapFile) {

    std::unique_ptr<FileSystem::FileAccessor> mapFileAccessor = FileSystem::Instance().loadFile(mapFile, mapFile);

    if (mapFileAccessor != NULL) {

        unloadTiles();

        if (FileSystem::Instance().traverseToElement(mapFileAccessor, "map")) {

            std::string tileset = "";
            int tilesAcross = 0, tilesDown = 0;
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
                char ignore = ' ';

                // Iterate and fill map with tiles based on data
                terrain.resize(mapHeight);
                entities.resize(mapHeight);

                for (int i = 0; i < terrain.size(); i++) {

                    terrain[i].resize(mapWidth);
                    entities[i].resize(mapWidth);

                    for (int j = 0; j < terrain[i].size(); j++) {

                        int x = 0, y = 0, tileNum = 0;

                        dataStream >> tileNum >> ignore;

                        if (tileNum != 0) {

                            if (tileNum == SPAWN_POINT_ID) {

                                spawnPoints.push_back(std::pair<int, int>(j, i));
                            }

                            tileNum--;
                            x = (tileNum % tilesAcross) * tileWidth;
                            y = ((int)(tileNum / tilesAcross)) * tileHeight;

                            terrain[i][j] = createTile(tileset.c_str(), tileWidth, tileHeight, x, y, j * tileWidth, i * tileHeight, false, LOWEST_PRIORITY);
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
                char ignore = ' ';

                // Iterate and fill map with tiles based on data
                objects.resize(mapHeight);

                for (int i = 0; i < objects.size(); i++) {

                    objects[i].resize(mapWidth);

                    for (int j = 0; j < objects[i].size(); j++) {

                        int x = 0, y = 0, tileNum = 0;

                        dataStream >> tileNum >> ignore;

                        if (tileNum != 0) {

                            tileNum--;
                            x = (tileNum % tilesAcross) * tileWidth;
                            y = ((int)(tileNum / tilesAcross)) * tileHeight;

                            objects[i][j] = createTile(tileset.c_str(), tileWidth, tileHeight, x, y, j * tileWidth, i * tileHeight, true, LOW_PRIORITY);
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

// Take the given entity and place him in the map grid
bool Terrain::placeEntityOnMap(GameObject *entity, int posX, int posY) {

    if (posY >= 0 && posY < entities.size() 
        && posX >= 0 && posX < entities[0].size()
        && entity != NULL
        ) {

        if (entities[posY][posX] == NULL) {

            Transform *trans = entity->getTransform();

            if (trans != NULL) {

                trans->position.x = posX * tileWidth;
                trans->position.y = posY * tileHeight;
            }

            entities[posY][posX] = entity;

            return true;
        }
    }

    return false;
}

// Take the given entity and give it the correct position without tracking it on the grid
bool Terrain::placeEntityOnMapNoCollision(GameObject *entity, int posX, int posY) {

    if (posY >= 0 && posY < entities.size()
        && posX >= 0 && posX < entities[0].size()
        && entity != NULL
        ) {

        Transform *trans = entity->getTransform();

        if (trans != NULL) {

            trans->position.x = posX * tileWidth;
            trans->position.y = posY * tileHeight;
        }

        return true;
    }

    return false;
}

// Remove an entity from the map, making it none collidable
bool Terrain::removeEntityFromMap(int posX, int posY) {

    if (posY >= 0 && posY < entities.size()
        && posX >= 0 && posX < entities[0].size()
        ) {

        if (entities[posY][posX] != NULL) {

            entities[posY][posX] = NULL;

            return true;
        }
    }

    return false;
}

// Check if you can move to the given square, then move the game object
bool Terrain::requestMoveEntity(Transform *trans, int posX, int posY, int distX, int distY) {

    if (entities[posY][posX] != NULL && trans != NULL) {
        if (entities[posY + distY][posX + distX] == NULL && objects[posY + distY][posX + distX] == NULL) {

            entities[posY + distY][posX + distX] = entities[posY][posX];
            entities[posY][posX] = NULL;

            trans->position.x = (posX + distX) * tileWidth;
            trans->position.y = (posY + distY) * tileHeight;

            return true;
        }
    }

    return false;
}

// Check if an entity is at the given coordinates and pass a reference if so
GameObject *Terrain::checkCollisionOnMap(int posX, int posY) {

    if (posY >= 0 && posY < entities.size()
        && posX >= 0 && posX < entities[0].size()
        ) {

        if (entities[posY][posX] != NULL) {

            return entities[posY][posX];
        }

        return objects[posY][posX];
    }

    return NULL;
}

// Remove the game object at the given coordinates from the map and destroy the object
bool Terrain::removeAndDestroyObject(int posX, int posY) {

    if (posY >= 0 && posY < entities.size()
        && posX >= 0 && posX < entities[0].size()
        ) {

        if (entities[posY][posX] != NULL) {

            entities[posY][posX]->destroy();
            entities[posY][posX] = NULL;

            return true;
        }
        else if (objects[posY][posX] != NULL) {

            objects[posY][posX]->destroy();
            objects[posY][posX] = NULL;

            return true;
        }
    }

    return false;
}