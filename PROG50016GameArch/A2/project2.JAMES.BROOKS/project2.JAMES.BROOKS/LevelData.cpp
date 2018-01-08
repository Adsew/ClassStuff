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
#include "AnimatedSprite.h"
#include "PlayerControls.h"
#include "Terrain.h"
#include "Bomb.h"
#include "Transform.h"
#include "LevelData.h"


IMPLEMENT_COMPONENT(LevelData);


LevelData::LevelData(unsigned int uniqueID)
    : Component(uniqueID, "LevelData") {

    bombPoolID = -1;

    score = 0;

    setupPerformed = false;
}

LevelData::LevelData(unsigned int uniqueID, const char *type)
    : Component(uniqueID, type) {

    bombPoolID = -1;

    score = 0;

    setupPerformed = false;
}

LevelData::~LevelData() {

    GameObjectManager::Instance().destroyObjectPool(bombPoolID);
}

void LevelData::initialize() {


}

void LevelData::update() {

    if (!setupPerformed) {

        setupLevel();
    }
}

void LevelData::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    int bombPoolSize = 0;

    FileSystem::Instance().getAttribute(accessor, "score", score);

    if (FileSystem::Instance().getAttribute(accessor, "bombPoolSize", bombPoolSize)) {

        // Build the bomb pool for participating entities
        GameObject *bombSample = GameObjectManager::Instance().createGameObject();
        bombSample->setName("Bomb");

        bombSample->setScene(this->gameObject);

        bombSample->addComponent(ComponentManager::Instance().createComponent("AnimatedSprite"));
        bombSample->addComponent(ComponentManager::Instance().createComponent("Bomb"));

        bombPoolID = GameObjectManager::Instance().createObjectPool(bombSample, bombPoolSize);

        bombSample->destroy();
    }
}

Component &LevelData::operator=(const Component &comp) {

    const LevelData *orig = (const LevelData *)&comp;

    score = orig->score;

    return *this;
}

// Perform a one time setup spawning the player and enemies and setting up object pool
void LevelData::setupLevel() {

    map = (Terrain *)this->gameObject->getComponent("Terrain");

    if (map != NULL) {

        if (map->spawnPoints.size() > 0) {

            std::list<std::pair<int, int>>::iterator iter = map->spawnPoints.begin();

            // Start with setting up player
            GameObject *player = GameObjectManager::Instance().createGameObjectFromPrefab("Player.prefab");

            if (player != NULL) {

                PlayerControls *pCont = (PlayerControls *)player->getComponent("PlayerControls");

                if (pCont != NULL) {

                    pCont->setMap(map);
                }

                Transform *pTrans = player->getTransform();

                pTrans->position.x = (float)(iter->first * map->tileWidth);
                pTrans->position.y = (float)(iter->second * map->tileHeight);

                player->setScene(this->gameObject);

                map->entities[iter->first][iter->second] = player;
            }

            iter++;

            // Now spawn and setup enemies
            for (iter; iter != map->spawnPoints.end(); iter++) {

                // Create enemies
            }
        }

        setupPerformed = true;
    }
}

// Increase current score by X points
void LevelData::increaseScore(int points) {

    score += points;
}

/* Gets/Sets */

unsigned int LevelData::getBombPoolID() {

    return bombPoolID;
}
