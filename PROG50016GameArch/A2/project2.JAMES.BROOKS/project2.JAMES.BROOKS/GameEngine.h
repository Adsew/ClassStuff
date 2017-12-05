#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

/*
Student: James Brooks
Class: Game Architecture

File: GameEngine.h

Class: GameEngine

Description: Holds the game loop and runs the major systems that run the game.
*/


class ISystem;


class GameEngine {

private:
	
    GameEngine() = default;
	
    ~GameEngine() = default;
	
    GameEngine(const GameEngine& other) = default;

public:

    inline static GameEngine& Instance() {

        static GameEngine instance;

        return instance;
    }

    void initialize();

    void gameLoop();
};

#endif // !GAME_ENGINE_H
