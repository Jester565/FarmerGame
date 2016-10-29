#pragma once
#include <allegro5/color.h>

class PhysicsBody;
class World;

class Bullet
{
public:
	static const float BULLET_W;
	static const float BULLET_H;
	static const float BULLET_SPEED;
	static const int BULLET_CATEGORY = 0x0008;
	static const int MAX_DIS = 50;
	static const int DAMAGE = 1;

	Bullet(World* world, float mX, float mY, float angle, int groupID, ALLEGRO_COLOR bulletColor);
	
	void draw();

	void drawLight();

	void setFinished()
	{
		finished = true;
	}

	bool isFinished()
	{
		return finished;
	}

	int getDamage()
	{
		return DAMAGE;
	}
	
	~Bullet();

private:
	ALLEGRO_COLOR bulletColor;
	PhysicsBody* physBody;
	World* world;
	float dis;
	float vX;
	float vY;
	bool finished;
};

