#pragma once
#include <iostream>

class Platform;

class Mover
{
public:
	static bool IsMover(int category);

	static const int MOVER_CATEGORY = 0x0002;

	Mover(int maxHealth);

	void setPlatformVX(bool onPlatform, float vX, Platform* platform);

	void damage(int dmg)
	{
		std::cout << dmg << std::endl;
		health -= dmg;
	}

	bool isDead()
	{
		return health <= 0;
	}

	~Mover();

protected:
	float platformVX;
	bool onPlatform;
	Platform* currentPlatform;
	int health;
};

