#pragma once
#include <Image.h>
#include <CircleLightSource.h>

class World;
class Platform;

class Elevator
{
public:
	static const int ELV_W = 460;
	static const int ELV_H = 1500;
	static const int EL_PLAT_W = 240;
	static const int EL_PLAT_H = 50;
	
	Elevator(World* world, float mX, float mY);

	void draw();

	bool isFinished();

	~Elevator();

private:
	Platform* platform;
	AllegroExt::Graphics::Image* img;
	World* world;
	float mX;
	float mY;
	lighting::CircleLightSource* ls1;
	lighting::CircleLightSource* ls2;
	lighting::CircleLightSource* ls3;
	lighting::CircleLightSource* ls4;
};

