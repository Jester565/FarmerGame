#include "Platform.h"
#include "PhysicsRectangle.h"
#include "World.h"
#include "Mover.h"
#include "Bullet.h"
#include "DigSite.h"
#include "PlatLight.h"
#include <LightBlockerContainer.h>
#include <ShapeRenderer.h>
#include <Core.h>

AllegroExt::Graphics::Image* Platform::Img1 = nullptr;

Platform::Platform(World* world, float w, float h, std::pair <float, float> cord1, std::pair <float, float> cord2, float speed, bool moverNeeded)
	:world(world), dis(0), speed(speed), moverNeeded(moverNeeded)
{
	if (Img1 == nullptr)
	{
		Img1 = new AllegroExt::Graphics::Image("dirtPlat.png");
	}
	img = Img1;
	b2FixtureDef physFixDef;
	physFixDef.filter.groupIndex = PLATFORM_GROUP_ID;
	physFixDef.filter.categoryBits = PLATFORM_CATEGORY;
	physFixDef.filter.maskBits = Bullet::BULLET_CATEGORY | Mover::MOVER_CATEGORY;
	physFixDef.density = 1020;
	physFixDef.friction = 1;
	physFixDef.userData = (void*)this;
	maxDis = sqrt(pow(cord2.first - cord1.first, 2) + pow(cord2.second - cord1.second, 2));
	float angle = atan2(cord2.second - cord1.second, cord2.first - cord1.first);
	vX = cos(angle) * speed;
	vY = sin(angle) * speed;
	physRect = new PhysicsRectangle(world, BODY_KINEM, physFixDef, cord1.first, cord1.second, w, h, 0, 255, 0, 0, 255);
	lbc = new lighting::LightBlockerContainer(world->getLightLayer());
	lbc->initSquare(w * B2D_SCALE, h * B2D_SCALE);
}

Platform::Platform(World * world, float w, float h, std::pair<float, float> cord1, std::pair<float, float> cord2, float speed, const std::string & path, int test)
	:world(world), dis(0), speed(speed), moverNeeded(moverNeeded)
{
	img = new AllegroExt::Graphics::Image(path);
	b2FixtureDef physFixDef;
	physFixDef.filter.groupIndex = PLATFORM_GROUP_ID;
	physFixDef.filter.categoryBits = PLATFORM_CATEGORY;
	physFixDef.filter.maskBits = Bullet::BULLET_CATEGORY | Mover::MOVER_CATEGORY;
	physFixDef.density = 1020;
	physFixDef.friction = 1;
	physFixDef.userData = (void*)this;
	maxDis = sqrt(pow(cord2.first - cord1.first, 2) + pow(cord2.second - cord1.second, 2));
	float angle = atan2(cord2.second - cord1.second, cord2.first - cord1.first);
	vX = cos(angle) * speed;
	vY = sin(angle) * speed;
	physRect = new PhysicsRectangle(world, BODY_KINEM, physFixDef, cord1.first, cord1.second, w, h, 0, 255, 0, 0, 255);
	lbc = new lighting::LightBlockerContainer(world->getLightLayer());
	lbc->initSquare(w * B2D_SCALE, h * B2D_SCALE);
}

Platform::Platform(World * world, float x, float y, float w, float h)
	:world(world), moverNeeded(false)
{
	if (Img1 == nullptr)
	{
		Img1 = new AllegroExt::Graphics::Image("dirtPlat.png");
	}
	img = Img1;
	b2FixtureDef physFixDef;
	physFixDef.filter.groupIndex = PLATFORM_GROUP_ID;
	physFixDef.filter.categoryBits = PLATFORM_CATEGORY;
	physFixDef.filter.maskBits = Bullet::BULLET_CATEGORY | Mover::MOVER_CATEGORY;
	physFixDef.density = 1020;
	physFixDef.friction = 1;
	physFixDef.userData = (void*)this;
	maxDis = 1;
	vX = 0;
	vY = 0;
	speed = 0;
	physRect = new PhysicsRectangle(world, BODY_KINEM, physFixDef, x, y, w, h, 0, 255, 0, 0, 255);
	lbc = new lighting::LightBlockerContainer(world->getLightLayer());
	lbc->initSquare(w * B2D_SCALE, h * B2D_SCALE);
}


void Platform::draw()
{
	if ((vX != 0 || vY != 0) && (movers.size() > 0 || !moverNeeded))
	{
		dis += abs(speed * (AllegroExt::Core::rate / AllegroExt::Core::DEFAULT_FPS_CAP));
		if (dis > maxDis)
		{
			vX = -vX;
			vY = -vY;
			dis = 0;
			for (auto it = movers.begin(); it != movers.end(); it++)
			{
				it->first->setPlatformVX(true, vX, this);
			}
		}
		b2Vec2 physVel(vX, vY);
		physRect->getBody()->SetLinearVelocity(physVel);
	}
	else if (moverNeeded)
	{
		b2Vec2 physVel(0, 0);
		physRect->getBody()->SetLinearVelocity(physVel);
	}
	int x = (physRect->getX() - world->getMeterWorldX()) * B2D_SCALE;
	int y = -(physRect->getY() - world->getMeterWorldY()) * B2D_SCALE;
	for (int i = 0; i < platLights.size(); i++)
	{
		platLights.at(i)->update(x, y - (getMH() / 2) * B2D_SCALE);
	}
	for (int i = 0; i < digSites.size(); i++)
	{
		digSites.at(i)->draw();
	}
	img->setImageOriginScaled(.5, .5);
	img->draw(x, y, physRect->getW() * B2D_SCALE, physRect->getH() * B2D_SCALE);
	lbc->setXY(x - (physRect->getW() / 2) * B2D_SCALE, y - (physRect->getH() / 2) * B2D_SCALE);
}

void Platform::addPlatLight(PlatLight * platLight)
{
	platLights.push_back(platLight);
}

void Platform::addDigSite(float offX)
{
	digSites.push_back(new DigSite(world, this, offX));
}

float Platform::getMX()
{
	return physRect->getX();
}

float Platform::getMY()
{
	return physRect->getY();
}

float Platform::getMW()
{
	return physRect->getW();
}

float Platform::getMH()
{
	return physRect->getH();
}

Platform::~Platform()
{
	delete physRect;
	physRect = nullptr;
}
