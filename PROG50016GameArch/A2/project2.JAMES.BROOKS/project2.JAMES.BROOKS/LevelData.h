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

class LevelData : public Component {

    REGISTER_COMPONENT(LevelData);


    /***** Variables *****/

protected:

    int score;


    /***** Functions *****/

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
};

#endif // !LEVEL_DATA_H
