#include "Mover.h"
#include "PotatoMan.h"
#include "Farmer.h"

Mover::Mover(int maxHealth)
	:platformVX(0), onPlatform(false), health(maxHealth), currentPlatform(nullptr)
{
}

void Mover::setPlatformVX(bool onPlatform, float vX, Platform* platform)
{
	this->onPlatform = onPlatform;
	platformVX = vX;
	currentPlatform = platform;
}

Mover::~Mover()
{
}

bool Mover::IsMover(int category)
{
	if (category == Mover::MOVER_CATEGORY)
	{
		return true;
	}
	return false;
}
