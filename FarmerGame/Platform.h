#pragma once
#include "Mover.h"
#include <Image.h>
#include <iostream>
#include <map>
#include <vector>
#include <LightBlockerContainer.h>

class World;
class PhysicsRectangle;
class Mover;
class DigSite;
class PlatLight;

class Platform
{
public:
	static const int PLATFORM_CATEGORY = 0x0001;
	static const int PLATFORM_GROUP_ID = -2;
	Platform(World* world, float w, float h, std::pair <float, float> cord1, std::pair <float, float> cord2, float speed, bool moverNeeded);

	Platform(World* world, float w, float h, std::pair <float, float> cord1, std::pair <float, float> cord2, float speed, const std::string& path, int test);

	Platform(World* world, float x, float y, float w, float h);

	void draw();

	void setMoverNeeded()
	{
		moverNeeded = true;
	}

	void addMover(Mover* mover)
	{
		movers.emplace(mover, false);
		mover->setPlatformVX(true, vX, this);
	}

	void removeMover(Mover* mover)
	{
		movers.erase(mover);
		mover->setPlatformVX(false, 0, nullptr);
	}

	std::vector <DigSite*> getDigSites()
	{
		return digSites;
	}

	void addPlatLight(PlatLight* platLight);

	void addDigSite(float offX);

	float getMX();

	float getMY();

	float getMW();

	float getMH();

	~Platform();

private:
	static AllegroExt::Graphics::Image* Img1;
	std::map <Mover*, bool> movers;
	std::vector <DigSite*> digSites;
	std::vector <PlatLight*> platLights;
	PhysicsRectangle* physRect;
	AllegroExt::Graphics::Image* img;
	World* world;
	lighting::LightBlockerContainer* lbc;
	float vX;
	float vY;
	float dis;
	float maxDis;
	float speed;
	bool moverNeeded;
};

