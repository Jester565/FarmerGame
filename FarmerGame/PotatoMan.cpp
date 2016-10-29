#include "PotatoMan.h"
#include "PhysicsBody.h"
#include "World.h"
#include "Platform.h"
#include "Farmer.h"
#include "RayCaster.h"
#include "Bullet.h"
#include "Gun.h"
#include "AniPart.h"
#include <Box2D/Box2D.h>

const float PotatoMan::POTATO_W = 3.4;
const float PotatoMan::POTATO_H = 7.7;
const float PotatoMan::POTATO_SCALE = 1.6;
const float PotatoMan::POTATO_SPEED = 6;

PotatoMan::PotatoMan(World * world, float mX, float mY)
	:Mover(POTATO_MAX_HEALTH), world(world), vX(POTATO_SPEED)
{
	physBody = new PhysicsBody(world, BODY_DYNAM, mX, mY, 0);
	b2FixtureDef playerFixDef;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(POTATO_W / 2, POTATO_H / 2);
	playerFixDef.shape = &boxShape;
	playerFixDef.shape = &boxShape;
	playerFixDef.density = 1000;
	playerFixDef.restitution = 0;
	playerFixDef.friction = .9;
	playerFixDef.filter.groupIndex = POTATO_GROUP_ID;
	playerFixDef.userData = (void*)this;
	playerFixDef.filter.categoryBits = MOVER_CATEGORY;
	playerFixDef.filter.maskBits = Platform::PLATFORM_CATEGORY | Bullet::BULLET_CATEGORY;
	physBody->setFixedRotation(true);
	physBody->getBody()->CreateFixture(&playerFixDef);
	physBody->setW(POTATO_W);
	physBody->setH(POTATO_H);
	physBody->setBmp();
	playerFixDef.density = 1;
	playerFixDef.friction = 0;
	boxShape.SetAsBox(POTATO_W / 20.0, POTATO_H / 2.0, b2Vec2(-POTATO_W / 2, 0), 0);
	physBody->getBody()->CreateFixture(&playerFixDef);
	boxShape.SetAsBox(POTATO_W / 20.0, POTATO_H / 2.0, b2Vec2(POTATO_W / 2, 0), 0);
	physBody->getBody()->CreateFixture(&playerFixDef);
	gun = new Gun(world, "alienshot.ogg", POTATO_GROUP_ID);
	gun->setColor(0, 1, 0);
	torso = new AniPart("potatoTorso.png", 70 * POTATO_SCALE, 92 * POTATO_SCALE, 35 * POTATO_SCALE, 41 * POTATO_SCALE);
	wheel = new AniPart("potatoWheel.png", 50 * POTATO_SCALE, 50 * POTATO_SCALE, 25 * POTATO_SCALE, 25 * POTATO_SCALE);
	arm = new AniPart("potatoArm.png", 20 * POTATO_SCALE, 50 * POTATO_SCALE, 10 * POTATO_SCALE, 2 * POTATO_SCALE);
	torso->createMoveJoint(wheel, 35 * POTATO_SCALE, 75 * POTATO_SCALE);
	torso->createMoveJoint(arm, 35 * POTATO_SCALE, 41 * POTATO_SCALE);
	int pX = ((physBody->getX() - world->getMeterWorldX()) * B2D_SCALE);
	int pY = (-(physBody->getY() - world->getMeterWorldY()) * B2D_SCALE);
	torso->setXY(pX, pY + POTATO_Y_OFF);
}

void PotatoMan::draw()
{
	float farmerX = world->getFarmer()->getBody()->getX();
	float farmerY = world->getFarmer()->getBody()->getY() + 2;
	float dis = sqrt(pow(farmerY - physBody->getY(), 2) + pow(farmerX - physBody->getX(), 2));
	float angle = atan2(farmerY - physBody->getY(), farmerX - physBody->getX());
	float gunX = physBody->getX();
	float gunY = physBody->getY() + 1.8;
	bool shot = false;
	if (dis < MAX_SIGHT_DIS && !world->getFarmer()->isDead())
	{
		int contactGID = world->rayCast(b2Vec2(physBody->getX(), physBody->getY()), b2Vec2(farmerX, farmerY), POTATO_GROUP_ID);
		if (contactGID == Farmer::FARMER_GROUP_ID)
		{
			gun->shoot(gunX, gunY, angle + ((rand() % 10) - 5) * 3.14 / 180);
			b2Vec2 vel = physBody->getBody()->GetLinearVelocity();
			physBody->getBody()->ApplyLinearImpulse(b2Vec2((platformVX - vel.x) * physBody->getBody()->GetMass(), 0), physBody->getBody()->GetWorldCenter(), true);
			shot = true;
	 	}
	}
	if (!shot)
	{
		if (vX > 0)
		{
			if (currentPlatform != nullptr)
			{
				if (physBody->getX() >= currentPlatform->getMX() + currentPlatform->getMW() / 4.0)
				{
					vX = -POTATO_SPEED;
				}
			}
		}
		else
		{
			if (currentPlatform != nullptr)
			{
				if (physBody->getX() <= currentPlatform->getMX() - currentPlatform->getMW() / 4.0)
				{
					vX = POTATO_SPEED;
				}
			}
		}
		if (currentPlatform != nullptr)
		{
			b2Vec2 vel = physBody->getBody()->GetLinearVelocity();
			physBody->getBody()->ApplyLinearImpulse(b2Vec2((vX + platformVX - vel.x) * physBody->getBody()->GetMass(), 0), physBody->getBody()->GetWorldCenter(), true);
		}
	}
	gun->draw(gunX, gunY, angle);
	int pX = ((physBody->getX() - world->getMeterWorldX()) * B2D_SCALE);
	int pY = (-(physBody->getY() - world->getMeterWorldY()) * B2D_SCALE);
	torso->setXY(pX, pY + POTATO_Y_OFF);
	if (angle < 0)
	{
		angle += M_PI * 2;
	}
	if (angle <= M_PI / 2 || angle >= (3 * M_PI) / 2)
	{
		if (horzFlip)
		{
			torso->setFlip(false, false);
			arm->setFlip(false, false);
			wheel->setFlip(false, false);
			horzFlip = false;
		}
	}
	else
	{
		if (!horzFlip)
		{
			torso->setFlip(true, false);
			arm->setFlip(true, false);
			wheel->setFlip(true, false);
			horzFlip = true;
		}
	}
	arm->rotate(-angle - M_PI / 2);
	torso->draw();
	arm->draw();
	wheel->draw();
}


PotatoMan::~PotatoMan()
{
	delete physBody;
	physBody = nullptr;
}
