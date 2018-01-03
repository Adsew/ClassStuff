#ifndef TERRAIN_H
#define TERRAIN_H

/*
Student: James Brooks
Class: Game Architecture

File: Terrain.h

Class: Terrain

Description: Keeps track of map data for the current level.
*/


#include "Component.h"


class Terrain : public Component {

    REGISTER_COMPONENT(Terrain);


    /***** Variables *****/

protected:

    // Parallel maps, terrain is ground, objects are collidable data
    std::vector<std::vector<GameObject *>> terrain;
    std::vector<std::vector<GameObject *>> objects;


    /***** Functions *****/

protected:
    
    Terrain(unsigned int uniqueID);

    Terrain(unsigned int uniqueID, const char *compType);
    
    virtual ~Terrain();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

    // Create a tile gameobject with the given properties
    GameObject *createTile(const char *tileAssetName, int w, int h, int xOrig, int yOrig, int xPos, int yPos, bool collider);

    // Unload tiles held by the map, if any
    void unloadTiles();

public:

    // Load a map file and create the tiles needed
    void loadMapFile(const char *mapFile);
};

#endif // !TERRAIN_H
