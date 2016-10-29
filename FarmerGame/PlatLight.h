#pragma once
#include <CircleLightSource.h>
#include <DirectionalLightSource.h>
#include <Image.h>

class PlatLight
{
public:
	PlatLight(lighting::CircleLightSource* lightSource, float offPX, float offPY);

	PlatLight(lighting::CircleLightSource* lightSource, float offPX, float offPY, const std::string& polePath, int imgW, int imgH, bool inverted = false);

	void update(float pX, float pY);

	~PlatLight();

private:
	AllegroExt::Graphics::Image* poleImg;
	lighting::CircleLightSource* lightSource;
	float imgW;
	float imgH;
	float offPX;
	float offPY;
};

