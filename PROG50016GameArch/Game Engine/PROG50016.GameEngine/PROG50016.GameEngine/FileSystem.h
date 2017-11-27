#pragma once

#include <string>
#include "ISystem.h"

class FileSystem : public ISystem
{

public:

	inline static FileSystem& Instance()
	{
		static FileSystem instance;

		return instance;
	}

private:

    FileSystem() = default;

    ~FileSystem() = default;

    FileSystem(const FileSystem& other) = default;

    friend class GameEngine;

protected:

	void initialize() override;

	void update(float _deltaTime) override;

public:

    void load(std::string &name);
};

