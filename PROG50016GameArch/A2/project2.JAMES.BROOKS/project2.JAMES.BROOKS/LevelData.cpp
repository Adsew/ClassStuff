/*
Student: James Brooks
Class: Game Architecture

File: LevelData.cpp

Class: LevelData

Description: Keeps track of the entities within the current level and the score.
*/


#include "Core.h"

#include "LevelData.h"


IMPLEMENT_COMPONENT(LevelData);


LevelData::LevelData(unsigned int uniqueID)
    : Component(uniqueID, "LevelData") {

    score = 0;
}

LevelData::LevelData(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    score = 0;
}

LevelData::~LevelData() {


}

void LevelData::initialize() {


}

void LevelData::update() {


}

void LevelData::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    FileSystem::Instance().getAttribute(accessor, "score", score);
}

Component &LevelData::operator=(const Component &comp) {

    const LevelData *orig = (const LevelData *)&comp;

    score = orig->score;

    return *this;
}

// Increase current score by X points
void LevelData::increaseScore(int points) {

    score += points;
}