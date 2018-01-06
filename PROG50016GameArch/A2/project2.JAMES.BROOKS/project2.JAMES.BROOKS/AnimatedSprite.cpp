/*
Student: James Brooks
Class: Game Architecture

File: AnimatedSprite.h

Class: AnimatedSprite

Description: A small image to be rendered to the screen. Animated over time.
*/


#define S_WIDTH 0
#define S_HEIGHT 1
#define S_X_ORIGIN 2
#define S_Y_ORIGIN 3
#define S_STEP_COUNT 4
#define S_FPS 5


#include "Core.h"

#include "Timer.h"
#include "TextureAsset.h"
#include "AssetManager.h"
#include "Transform.h"
#include "AnimatedSprite.h"


IMPLEMENT_COMPONENT(AnimatedSprite);


AnimatedSprite::AnimatedSprite(unsigned int uniqueID) 
    : Sprite(uniqueID, "AnimatedSprite") {

    currentAnim = -1;
    step = 0;
    playCount = 0;
    numTimesPlayed = 0;

    deltaTime = 0;
}

AnimatedSprite::AnimatedSprite(unsigned int uniqueID, const char *type)
    : Sprite(uniqueID, type) {

    currentAnim = -1;
    step = 0;
    playCount = 0;
    numTimesPlayed = 0;

    deltaTime = 0;
}

AnimatedSprite::~AnimatedSprite() {

    for (int i = 0; i < animations.size(); i++) {

        delete animations[i];
        animations[i] = NULL;
    }
}

void AnimatedSprite::update() {

    Transform *trans = gameObject->getTransform();

    if (trans != NULL) {

        sprite.setPosition(trans->position);
        sprite.setRotation(trans->rotation);
        sprite.setScale(trans->scale);
    }

    // Only animate if it has not finished playing
    if (!hasPlayedCountTimes()) {

        float timeNeeded = ( 1.0f / animations[currentAnim][S_FPS] ) * 2;
        deltaTime += Timer::Instance().getDelta();

        if (deltaTime >= timeNeeded) {
            
            deltaTime -= timeNeeded;

            step = (step + 1) % animations[currentAnim][S_STEP_COUNT];
            spriteRect.left = step * animations[currentAnim][S_WIDTH];

            sprite.setTextureRect(spriteRect);
        }
    }
}

void AnimatedSprite::load(std::unique_ptr<FileSystem::FileAccessor> &accessor) {

    std::string assetName = "";
    int priority = LOWEST_PRIORITY;

    if (FileSystem::Instance().getAttribute(accessor, "Asset", assetName)) {

        TextureAsset *temp = NULL;

        // Maintain asset reference count and make texture asset remains usable
        spriteImagePtr = AssetManager::Instance().getAsset(assetName.c_str());

        temp = (TextureAsset *)spriteImagePtr.get();

        if (temp != NULL) {

            sprite.setTexture(*(temp->getTexture()));
        }
        else {

            DEBUG_LOG("Sprite: Unable to retrieve texture asset for " << assetName.c_str() << ".");
        }
    }

    if (FileSystem::Instance().getAttribute(accessor, "priority", priority)) {

        setRenderPriority(priority);
    }

    if (FileSystem::Instance().traverseToChildElement(accessor)) {

        int *coords = NULL;

        do {

            coords = new int[6];

            FileSystem::Instance().getAttribute(accessor, "width", coords[S_WIDTH]);
            FileSystem::Instance().getAttribute(accessor, "height", coords[S_HEIGHT]);
            FileSystem::Instance().getAttribute(accessor, "xOrigin", coords[S_X_ORIGIN]);
            FileSystem::Instance().getAttribute(accessor, "yOrigin", coords[S_Y_ORIGIN]);
            FileSystem::Instance().getAttribute(accessor, "steps", coords[S_STEP_COUNT]);
            FileSystem::Instance().getAttribute(accessor, "fps", coords[S_FPS]);

            animations.push_back(coords);

        } while (FileSystem::Instance().traverseToSyblingElement(accessor));

        FileSystem::Instance().traverseToParentElement(accessor);

        setAnimation(0);
    }
}

// Set which animation is currently playing from the sprite sheet
bool AnimatedSprite::setAnimation(int animID) {

    if (animID >= 0 && animID < animations.size() && animID != currentAnim) {

        currentAnim = animID;
        step = 0;
        playCount = 0;
        numTimesPlayed = 0;
        deltaTime = 0;

        spriteRect.width = animations[currentAnim][S_WIDTH];
        spriteRect.height = animations[currentAnim][S_HEIGHT];
        spriteRect.left = animations[currentAnim][S_X_ORIGIN];
        spriteRect.top = animations[currentAnim][S_Y_ORIGIN];

        sprite.setTextureRect(spriteRect);

        return true;
    }

    return false;
}

// Return the number of animations loaded from the sprite
int AnimatedSprite::getAnimationCount() {

    return (int)animations.size();
}

// Set the number of times to play the current animation
// Infinite if not set after setAnimation call
void AnimatedSprite::setPlayCount(int numTimes) {

    playCount = numTimes;
    numTimesPlayed = 0;
}

// True if animation has played the set number of times by setPlayCount
bool AnimatedSprite::hasPlayedCountTimes() {

    if (numTimesPlayed >= playCount && playCount > 0) {

        return true;
    }

    return false;
}
