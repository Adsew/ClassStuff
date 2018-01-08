#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

/*
Student: James Brooks
Class: Game Architecture

File: LevelData.h

Class: LevelData

Description: Keeps track of the entities within the current level and the score.
*/


#include "Component.h"


class Terrain;


class LevelData : public Component {

    REGISTER_COMPONENT(LevelData);


    /***** Variables *****/

protected:

    Terrain *map;

    unsigned int bombPoolID;
    int score;

    bool setupPerformed;


    /***** Functions *****/

private:

    // Perform a one time setup spawning the player and enemies and setting up object pool
    void setupLevel();

protected:

    LevelData(unsigned int uniqueID);

    LevelData(unsigned int uniqueID, const char *type);

    ~LevelData();

    virtual void initialize() override;

    virtual void update() override;

    virtual void load(std::unique_ptr<FileSystem::FileAccessor> &accessor) override;

public:

    virtual Component &operator=(const Component &comp) override;

    // Increase current score by X points
    void increaseScore(int points);

        /* Gets/Sets */

    unsigned int getBombPoolID();
};

#endif // !LEVEL_DATA_H
