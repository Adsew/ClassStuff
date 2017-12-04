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

	void load(std::string _filename);

protected:
	void initialize() override;
	void update(float _deltaTime) override;

private:

	FileSystem() = default;
	~FileSystem() = default;
	FileSystem(const FileSystem& other) = default;

	friend class GameEngine;
};

