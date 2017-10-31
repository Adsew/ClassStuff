#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: SceneManager.h

Class: SceneManager

Description: Acts and the data controller between the active game scene
    and the input. It will contain what data is currently active in the
    game world.
*/


class Player;
class Zone;


class SceneManager {

private:

    Player *player;
    Zone *activeZone;
    
public:

    SceneManager();

    ~SceneManager();

    // Initialize input manager to a usable state
    void intialize();

    // Cycle update for input manager
    void update();

    // Display relavent metrics to screen
    void display();
};

#endif
