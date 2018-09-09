#pragma once
#include "Mover.h"
#include <SoundEffect.h>
#include <CircleLightSource.h>
#include <DirectionalLightSource.h>

class PhysicsBody;
class World;
class Gun;
class AniPart;

class Farmer : public Mover
{
public:
	static const float PLAYER_W;
	static const float PLAYER_H;
	static const float JUMP_FORCE;
	static const float PLAYER_SCALE;
	static const int FARMER_GROUP_ID = -1;
	static const int FARMER_MAX_HEALTH = 5;
	static const float GUN_OFF_PAR;
	static const float GUN_OFF_PERP;
	static const float LEG_MULT;
	static const int DIG_OFF = 2;

	Farmer(World* world, float mX, float mY);

	void draw();

	float getTransX()
	{
		return transX;
	}

	float getTransY()
	{
		return transY;
	}

	void addHealth(int hp)
	{
		if (!isDead())
		{
			if (health + hp > FARMER_MAX_HEALTH)
			{
				health = FARMER_MAX_HEALTH;
			}
			else
			{
				health += hp;
			}
		}
	}

	PhysicsBody* getBody()
	{
		return physBody;
	}

	int getHealth()
	{
		return health;
	}

	void setMovementDisabled(bool mode)
	{
		movementDisabled = mode;
	}

	void dig();

	~Farmer();

private:
	AllegroExt::Sound::SoundEffect* grass1;
	AllegroExt::Sound::SoundEffect* grass2;
	AllegroExt::Sound::SoundEffect* grass3;
	AniPart* torso;
	AniPart* topArm;
	AniPart* bottomArm;
	AniPart* topForearm;
	AniPart* bottomForearm;
	AniPart* topLeg;
	AniPart* bottomLeg;
	AniPart* gunImg;
	PhysicsBody* physBody;
	World* world;
	Gun* gun;
	float transX;
	float transY;
	float lastX;
	float lastY;
	float stepSoundTimer;
	float jumpTimer;
	bool horzFlip;
	float legAngle;
	bool legDir;
	bool movementDisabled;
	lighting::CircleLightSource* surroundLight;
	lighting::DirectionalLightSource* flashLight;
};

