#include "FileSystem.h"
#include "AssetManager.h"

void FileSystem::load(std::string _filename)
{
	XMLDocument doc;
	doc.LoadFile(_filename.c_str());

	if (doc.Error())
	{
		std::cout << "Error loading the file: " << _filename.c_str() << std::endl;
		return;
	}

	XMLElement* element;

	element = doc.FirstChildElement("Assets");
	if (element != nullptr)
	{
		AssetManager::Instance().load(element);
	}
}

void FileSystem::initialize()
{
}

void FileSystem::update(float _deltaTime)
{
}
