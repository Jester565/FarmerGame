#pragma once
#include <Image.h>

class Farmer;

class Item
{
public:
	Item();

	virtual void draw(float x, float y, float w, float h);
	
	virtual void use(Farmer* farmer) = 0;

	int getID()
	{
		return id;
	}

	~Item();
	
protected:
	AllegroExt::Graphics::Image* texture;
	int id;
};

