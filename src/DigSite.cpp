#include "DigSite.h"
#include "World.h"
#include "Platform.h"

AllegroExt::Graphics::Image* DigSite::texture = nullptr;
AllegroExt::Graphics::Image* DigSite::dugTexture = nullptr;

DigSite::DigSite(World* world, Platform* platform, float offMX)
	:world(world), boundPlatform(platform), offMX(offMX)
{
	if (texture == nullptr)
	{
		texture = new AllegroExt::Graphics::Image("digSite.png", DIGSITE_W, DIGSITE_H);
		dugTexture = new AllegroExt::Graphics::Image("digSiteDug.png", DIGSITE_W, DIGSITE_H);
	}
}

void DigSite::draw()
{
	int pX = ((boundPlatform->getMX() + offMX - world->getMeterWorldX()) * B2D_SCALE);
	int pY = (-(boundPlatform->getMY() + boundPlatform->getMH() / 2.0 - world->getMeterWorldY()) * B2D_SCALE);
	if (!dug)
	{
		texture->draw(pX, pY - DIGSITE_H);
	}
	else
	{
		dugTexture->draw(pX, pY - DIGSITE_H);
	}
}


DigSite::~DigSite()
{
}
