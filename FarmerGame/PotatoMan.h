#pragma once
#include "Mover.h"

class World;
class Gun;
class PhysicsBody;
class AniPart;

class PotatoMan : public Mover
{
public:
	static const float POTATO_W;
	static const float POTATO_H;
	static const int MAX_SIGHT_DIS = 50;
	static const int POTATO_GROUP_ID = -3;
	static const int POTATO_MAX_HEALTH = 3;
	static const int POTATO_Y_OFF = -20;
	static const float POTATO_SCALE;
	static const float POTATO_SPEED;
	
	PotatoMan(World* world, float mX, float mY);

	void draw();

	~PotatoMan();

private:
	AniPart* torso;
	AniPart* arm;
	AniPart* wheel;
	PhysicsBody* physBody;
	Gun* gun;
	World* world;
	float vX;
	bool horzFlip;
};

