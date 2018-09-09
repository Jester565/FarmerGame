#include "Elevator.h"
#include "World.h"
#include "PlatLight.h"
#include "Platform.h"
#include <LightLayer.h>
#include <CircleLightSource.h>

Elevator::Elevator(World * world, float mX, float mY)
	:world(world), mX(mX), mY(mY)
{
	platform = new Platform(world, EL_PLAT_W / B2D_SCALE, EL_PLAT_H / B2D_SCALE, std::make_pair(mX, mY), std::make_pair(mX, mY + 60), 3, "elevatorPlatform.png", 2);
	platform->setMoverNeeded();
	ls1 = new lighting::CircleLightSource(world->getLightLayer(), 400, 255, 0, 0);
	ls2 = new lighting::CircleLightSource(world->getLightLayer(), 400, 255, 0, 0);
	ls3 = new lighting::CircleLightSource(world->getLightLayer(), 300, 0, 0, 255);
	ls4 = new lighting::CircleLightSource(world->getLightLayer(), 300, 0, 0, 255);
	//circLS->setXY(600, 600);
	//platform->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post1.png", 30, -3.3 * B2D_SCALE));
	img = new AllegroExt::Graphics::Image("elevator.png", ELV_W, ELV_H);
}

void Elevator::draw()
{
	/*
	int x = ((mX - world->getMeterWorldX()) * B2D_SCALE);
	int y = (-(mY - world->getMeterWorldY()) * B2D_SCALE);
	x -= (ELV_W / 2) / B2D_SCALE;
	y -= ELV_H / B2D_SCALE;
	*/
	int x = ((mX - world->getMeterWorldX()) * B2D_SCALE);
	int y = (-(mY - world->getMeterWorldY()) * B2D_SCALE);
	x -= ELV_W / 2;
	y -= ELV_H;
	int yOff = 60;
	ls1->setXY(x + 96, y + 636 + yOff);
	ls2->setXY(x + 360, y + 283 + yOff);
	ls3->setXY(x + 96, y + 1167 + yOff);
	ls4->setXY(x + 360, y + 1167 + yOff);
	img->draw(x, y + yOff);
	platform->draw();
}

bool Elevator::isFinished()
{
	return (platform->getMY() > mY + 2);
}

Elevator::~Elevator()
{
}
