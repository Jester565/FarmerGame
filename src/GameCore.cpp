#include "GameCore.h"
#include "World.h"

GameCore::GameCore(const std::string& resourcePath)
	:AllegroExt::Core(resourcePath), fpsLogger(nullptr)
{
}

bool GameCore::init()
{
	if (Core::init())
	{
		fpsLogger = new AllegroExt::FPSLogger();
		world = new World();
		return true;
	}
	return false;
}

void GameCore::draw()
{
	world->draw();
	fpsLogger->draw(5, 10, 50);
}

void GameCore::destroyWorld()
{
	delete world;
	world = nullptr;
}

GameCore::~GameCore()
{
	
}
