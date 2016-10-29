#pragma once
#include <Image.h>

class World;
class Platform;

class DigSite
{
public:
	static const int DIGSITE_W = 100;
	static const int DIGSITE_H = 50;
	DigSite(World* world, Platform* platform, float offMX);

	void draw();

	bool isDug()
	{
		return dug;
	}

	void setAsDug()
	{
		dug = true;
	}

	float getOffMX()
	{
		return offMX;
	}

	~DigSite();

private:
	static AllegroExt::Graphics::Image* texture;
	static AllegroExt::Graphics::Image* dugTexture;
	Platform* boundPlatform;
	World* world;
	float offMX;
	bool dug;
};

