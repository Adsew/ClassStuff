/*
Student: James Brooks
Class: Game Architecture

File: LevelData.cpp

Class: LevelData

Description: Keeps track of the entities within the current level and the score.
*/


#include "Core.h"

#include "ComponentManager.h"
#include "GameObjectManager.h"
#include "LevelData.h"


IMPLEMENT_COMPONENT(LevelData);


LevelData::LevelData(unsigned int uniqueID)
    : Component(uniqueID, "LevelData") {

    // Build the bomb pool for participating entities
    GameObject *bombSample = GameObjectManager::Instance().createGameObject();
    bombSample->setName("Bomb");

    bombSample->addComponent(ComponentManager::Instance().createComponent("AnimatedSprite"));
    bombSample->addComponent(ComponentManager::Instance().createComponent("Bomb"));

    bombPoolID = GameObjectManager::Instance().createObjectPool(bombSample, 10);

    bombSample->destroy();

    score = 0;
}

LevelData::LevelData(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    // Build the bomb pool for participating entities
    GameObject *bombSample = GameObjectManager::Instance().createGameObject();
    bombSample->setName("Bomb");

    bombSample->addComponent(ComponentManager::Instance().createComponent("AnimatedSprite"));
    bombSample->addComponent(ComponentManager::Instance().createComponent("Bomb"));

    bombPoolID = GameObjectManager::Instance().createObjectPool(bombSample, 10);

    bombSample->destroy();

    score = 0;
}

LevelData::~LevelData() {

    GameObjectManager::Instance().destroyObjectPool(bombPoolID);
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

/* Gets/Sets */

unsigned int LevelData::getBombPoolID() {

    return bombPoolID;
}
