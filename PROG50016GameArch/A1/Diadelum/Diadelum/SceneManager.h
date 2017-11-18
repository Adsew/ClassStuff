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


#include <vector>
#include <list>


class Player;
class Zone;


class SceneManager {

private:

    /***** Variables *****/

    std::vector<void (SceneManager::*)(std::list<std::pair<int, std::string>> &)> actions;

    Player *player;
    
    Zone *activeZone;
    
    bool exitFlag;


    /***** Functions *****/

    void noAction(std::list<std::pair<int, std::string>> &action);

    void move(std::list<std::pair<int, std::string>> &action);

    void use(std::list<std::pair<int, std::string>> &action);

    void search(std::list<std::pair<int, std::string>> &action);

    void pickup(std::list<std::pair<int, std::string>> &action);

    void talk(std::list<std::pair<int, std::string>> &action);

    void attack(std::list<std::pair<int, std::string>> &action);

    void help(std::list<std::pair<int, std::string>> &action);

    void save(std::list<std::pair<int, std::string>> &action);

    void exit(std::list<std::pair<int, std::string>> &action);

public:

    SceneManager();

    ~SceneManager();

    // Initialize input manager to a usable state
    void intialize();

    // Cycle update for input manager
    bool update();
};

#endif
