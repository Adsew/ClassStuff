#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

/*
Student: James Brooks
Class: Game Architecture

File: AssetManager.h

Class: AssetManager

Description:
*/


class AssetManager {

public:

    /***** Functions *****/

    AssetManager();

    ~AssetManager();

    // Initialize asset manager to a usable point
    void initialize();

    // Cycle update for asset manager
    void update();

    // Display relavent data to screen
    void display();
};

#endif
