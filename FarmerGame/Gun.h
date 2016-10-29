#pragma once
#include <SoundEffect.h>
#include <allegro5/color.h>
#include <list>

class Bullet;
class World;

class Gun
{
public:
	static const int RATE_OF_FIRE = 30;

	Gun(World* world, const std::string& soundPath, int groupID);

	void setColor(float r, float g, float b);

	void draw(float x, float y, float angle);

	void shoot(float x, float y, float angle);

	~Gun();

private:
	ALLEGRO_COLOR bulletColor;
	AllegroExt::Sound::SoundEffect* soundEffect;
	World* world;
	int groupID;
	float timer;
};

