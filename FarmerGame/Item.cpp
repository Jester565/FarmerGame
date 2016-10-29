#include "Item.h"
#include "Farmer.h"

Item::Item()
	:texture(nullptr)
{
}

void Item::draw(float x, float y, float w, float h)
{
	texture->draw(x, y, w, h);
}


Item::~Item()
{
	delete texture;
	texture = nullptr;
}
