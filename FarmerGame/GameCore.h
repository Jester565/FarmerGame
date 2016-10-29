#pragma once
#include <Core.h>
#include <FPSLogger.h>

class World;

class GameCore : public AllegroExt::Core
{
public:
	GameCore(const std::string& resourcePath);

	bool init() override;

	void draw() override;

	void destroyWorld();

	~GameCore();

private:
	World* world;
	AllegroExt::FPSLogger* fpsLogger;
};

