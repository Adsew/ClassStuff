#ifndef SAVE_STATE_MANAGER_H
#define SAVE_STATE_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: SaveStateManager.h

Class: SaveStateManager

Description: Manages the files and data used to save and load the
    persistant state of the current game world.
*/


class Player;
class Zone;


class SaveStateManager {

private:

    SaveStateManager();

    SaveStateManager(SaveStateManager &ssm);

    ~SaveStateManager();

    SaveStateManager &operator=(SaveStateManager &ssm);

public:

    inline static SaveStateManager &Instance() {

        static SaveStateManager instance;

        return instance;
    }

    // Create a temp save file with a given name to work with (used with new games)
    void createTempSave(const char *name);

    // Create a temp save file with a given name to work with (used with new games)
    void createTempSave(std::string &name);

    // Load a pre-existing player from save file
    Player *loadPlayer(const char *name);

    // Load a pre-existing player from save file
    Player *loadPlayer(std::string &name);

    // Load a zone from the current player save
    Zone *loadZone(const char *zoneName, const char *saveName);

    // Load a zone from the current player save
    Zone *loadZone(std::string &zoneName, std::string &saveName);

    // Save the zone details to the player temp save file
    void saveZone(const char *playerName, Zone *zone);

    // Save the zone details to the player temp save file
    void saveZone(std::string &playerName, Zone *zone);

    // Save the game officially pushing it to a file
    bool saveGame(Player *player);
};

#endif
