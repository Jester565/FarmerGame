#include "PhysicsRectangle.h"
#include "World.h"
#include <allegro5/allegro.h>
#include <iostream>

/*
PhysicsRectangle::PhysicsRectangle(World * world, BodyMode bm, float x, float y, float w, float h, float degs)
	:PhysicsBody(world, bm, x, y, degs)
{
	b2FixtureDef boxFixDef;
	boxFixDef.density = 1;
	init(boxFixDef, w, h);
}
*/

PhysicsRectangle::PhysicsRectangle(World * world, BodyMode bm, b2FixtureDef & boxFixDef, float x, float y, float w, float h, float degs)
	:PhysicsBody(world, bm, x, y, degs)
{
	init(boxFixDef, w, h);
}

/*
PhysicsRectangle::PhysicsRectangle(World* world, BodyMode bm, float x, float y, float w, float h, float degs, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: PhysicsRectangle(world, bm, x, y, w, h, degs)
{
	initBmp(r, g, b, a);
}
*/

PhysicsRectangle::PhysicsRectangle(World* world, BodyMode bm, b2FixtureDef & boxFixDef, float x, float y, float w, float h, float degs, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: PhysicsRectangle(world, bm, boxFixDef, x, y, w, h, degs)
{
	initBmp(r, g, b, a);
}

void PhysicsRectangle::initBmp(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->bitmapW = w * B2D_SCALE;
	this->bitmapH = h * B2D_SCALE;
	bodyBitMap = al_create_bitmap(w * B2D_SCALE, h * B2D_SCALE);
	ALLEGRO_BITMAP* previousBitmap = al_get_target_bitmap();
	al_set_target_bitmap(bodyBitMap);
	al_clear_to_color(al_map_rgba(r, g, b, a));
	al_set_target_bitmap(previousBitmap);
}

void PhysicsRectangle::init(b2FixtureDef& boxFixDef, float w, float h)
{
	this->w = w;
	this->h = h;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(w / 2.0f, h / 2.0f);
	boxFixDef.shape = &boxShape;
	body->CreateFixture(&boxFixDef);
}

PhysicsRectangle::~PhysicsRectangle()
{
}
