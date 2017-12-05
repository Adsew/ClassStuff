#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

/*
Student: James Brooks
Class: Game Architecture

File: FileSyster.h

Class: FileSystem

Description: Lowest level of file loading. Calling this can return a file element
    to be sifted through for data.
*/


#include "ISystem.h"


class FileSystem : public ISystem {

    friend class GameEngine;

public:

	inline static FileSystem& Instance() {

		static FileSystem instance;

		return instance;
	}

private:

    FileSystem() = default;

    ~FileSystem() = default;

    FileSystem(const FileSystem& other) = default;

protected:

	void initialize() override;

	void update(float _deltaTime) override;

public:

    void load(std::string name);
};

#endif // !FILE_SYSTEM_H
