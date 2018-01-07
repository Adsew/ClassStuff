#ifndef TILE_H
#define TILE_H

/*
Student: James Brooks
Class: Game Architecture

File: Tile.h

Class: Tile

Description: Component that defines the type of tile in the terrain grid.
    Types are: Collidable, Not Collidable
*/


#include "Component.h"


class Tile : public Component {

    REGISTER_COMPONENT(Tile);


    /***** Variables *****/

protected:

    bool collidable;


    /***** Functions *****/

protected:
    
    Tile(unsigned int uniqueID);
    
    Tile(unsigned int uniqueID, const char *type);

    ~Tile();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    void setCollidable(bool c);

    bool isCollidable();
};

#endif // !TILE_H
