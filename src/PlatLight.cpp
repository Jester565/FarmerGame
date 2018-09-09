#include "PlatLight.h"

PlatLight::PlatLight(lighting::CircleLightSource * lightSource, float offMX, float offMY)
	:lightSource(lightSource), offPX(offMX), offPY(offMY), poleImg(nullptr)
{
}

PlatLight::PlatLight(lighting::CircleLightSource * lightSource, float offPX, float offPY, const std::string & polePath, int imgW, int imgH, bool inverted)
	:PlatLight(lightSource, offPX, offPY)
{
	this->imgW = imgW;
	if (inverted)
	{
		this->imgH = 0;
	}
	else
	{
		this->imgH = imgH;
	}
	poleImg = new AllegroExt::Graphics::Image(polePath, imgW, imgH);
}

void PlatLight::update(float pX, float pY)
{
	if (poleImg != nullptr)
	{
		poleImg->draw(pX + offPX - imgW / 2, pY - imgH);
	}
	lightSource->setXY(pX + offPX, pY + offPY);
}

PlatLight::~PlatLight()
{
}
