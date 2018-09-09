#include "Farmer.h"
#include "PhysicsBody.h"
#include "World.h"
#include "ContactListener.h"
#include "Platform.h"
#include "Gun.h"
#include "AniPart.h"
#include "DigSite.h"
#include "HUD.h"
#include "MedKit.h"
#include "MedShot.h"
#include <CircleLightSource.h>
#include <DirectionalLightSource.h>
#include <Core.h>
#include <Box2D/Box2D.h>
#include <InputManager.h>

const float Farmer::PLAYER_W = 1.2;
const float Farmer::PLAYER_H = 7.2;
const float Farmer::JUMP_FORCE = 25;
const float Farmer::PLAYER_SCALE = 1.6;
const float Farmer::LEG_MULT = 3;
const float Farmer::GUN_OFF_PAR = .7;
const float Farmer::GUN_OFF_PERP = .2;

Farmer::Farmer(World* world, float mX, float mY)
	:Mover(FARMER_MAX_HEALTH), lastX(mX), lastY(mY), transX(0), transY(0), world(world), jumpTimer(0), legAngle(0), movementDisabled(false)
{
	physBody = new PhysicsBody(world, BODY_DYNAM, mX, mY, 0);
	b2FixtureDef playerFixDef;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(PLAYER_W / 2, PLAYER_H / 2);
	playerFixDef.shape = &boxShape;
	playerFixDef.shape = &boxShape;
	playerFixDef.density = 1020;
	playerFixDef.restitution = 0;
	playerFixDef.friction = .9;
	playerFixDef.filter.groupIndex = FARMER_GROUP_ID;
	playerFixDef.filter.categoryBits = MOVER_CATEGORY;
	playerFixDef.userData = (void*)this;
	physBody->setFixedRotation(true);
	physBody->getBody()->CreateFixture(&playerFixDef);
	physBody->setW(PLAYER_W);
	physBody->setH(PLAYER_H);
	physBody->setBmp();
	playerFixDef.density = 1;
	playerFixDef.friction = 0;
	boxShape.SetAsBox(PLAYER_W / 20.0, PLAYER_H / 2.0, b2Vec2(-PLAYER_W / 2, 0), 0);
	physBody->getBody()->CreateFixture(&playerFixDef);
	boxShape.SetAsBox(PLAYER_W / 20.0, PLAYER_H / 2.0, b2Vec2(PLAYER_W / 2, 0), 0);
	physBody->getBody()->CreateFixture(&playerFixDef);
	b2FixtureDef sensorFixDef;
	b2PolygonShape sensorShape;
	sensorFixDef.density = 1000;
	sensorFixDef.filter.categoryBits = MOVER_CATEGORY;
	sensorFixDef.filter.groupIndex = FARMER_GROUP_ID;
	sensorFixDef.userData = (void*)this;
	sensorFixDef.isSensor = true;
	sensorShape.SetAsBox(PLAYER_W / 2.0, PLAYER_H / 20.0, b2Vec2(0, -PLAYER_H / 2), 0);
	sensorFixDef.shape = &sensorShape;
	b2Fixture* groundSensor = physBody->getBody()->CreateFixture(&sensorFixDef);
	gun = new Gun(world, "gunshot.ogg", FARMER_GROUP_ID);
	torso = new AniPart("torso.png", 24 * PLAYER_SCALE, 56 * PLAYER_SCALE, 12 * PLAYER_SCALE, 54 * PLAYER_SCALE);
	topArm = new AniPart("farmArm.png", 13 * PLAYER_SCALE, 21 * PLAYER_SCALE, 6.5 * PLAYER_SCALE, 3 * PLAYER_SCALE);
	topForearm = new AniPart("farmForearm.png", 9 * PLAYER_SCALE, 25 * PLAYER_SCALE, 4.5 * PLAYER_SCALE, 3 * PLAYER_SCALE);
	//bottomArm = new AniPart("farmArm.png", 14 * PLAYER_SCALE, 25 * PLAYER_SCALE, 6 * PLAYER_SCALE, 3 * PLAYER_SCALE);
	topLeg = new AniPart("farmLeg.png", 24 * PLAYER_SCALE, 42 * PLAYER_SCALE, 12 * PLAYER_SCALE, 3 * PLAYER_SCALE);
	bottomLeg = new AniPart("farmLeg.png", 24 * PLAYER_SCALE, 42 * PLAYER_SCALE, 12 * PLAYER_SCALE, 3 * PLAYER_SCALE);
	gunImg = new AniPart("gun.png", 18 * PLAYER_SCALE, 20 * PLAYER_SCALE, 9 * PLAYER_SCALE, 1 * PLAYER_SCALE);
	torso->createMoveJoint(topArm, 12 * PLAYER_SCALE, 22 * PLAYER_SCALE);
	torso->createMoveJoint(topLeg, 12 * PLAYER_SCALE, 52 * PLAYER_SCALE);
	torso->createMoveJoint(bottomLeg, 12 * PLAYER_SCALE, 52 * PLAYER_SCALE);
	topArm->createMoveJoint(topForearm, 6.5 * PLAYER_SCALE, 19 * PLAYER_SCALE);
	topForearm->createMoveJoint(gunImg, 4.5 * PLAYER_SCALE, 20 * PLAYER_SCALE);
	torso->setXY(STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2 + 12);
	surroundLight = new lighting::CircleLightSource(world->getLightLayer(), 100, 200, 200, 200);
	flashLight = new lighting::DirectionalLightSource(world->getLightLayer(), 600, 40, 200, 200, 200);
	grass1 = new AllegroExt::Sound::SoundEffect(AllegroExt::Core::GetSoundManager(), "grass1.wav", 1);
	grass2 = new AllegroExt::Sound::SoundEffect(AllegroExt::Core::GetSoundManager(), "grass2.wav", 1);
	grass3 = new AllegroExt::Sound::SoundEffect(AllegroExt::Core::GetSoundManager(), "grass3.wav", 1);
	AllegroExt::Core::GetSoundManager()->setIDVol(1, 0);
}

void Farmer::draw()
{
	if (stepSoundTimer > 0)
	{
		stepSoundTimer -= AllegroExt::Core::rate;
	}
	surroundLight->setXY(STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2 - 40);
	transX = physBody->getX() - lastX;
	transY = physBody->getY() - lastY;
	lastX = physBody->getX();
	lastY = physBody->getY();
	b2Vec2 vel = physBody->getBody()->GetLinearVelocity();
	float desiredXV = 0;
	if (!isDead() && !movementDisabled && AllegroExt::Input::InputManager::keyPressed('a') != AllegroExt::Input::InputManager::keyPressed('d'))
	{
		if (AllegroExt::Input::InputManager::keyPressed('a'))
		{
			desiredXV = -15;
		}
		if (AllegroExt::Input::InputManager::keyPressed('d'))
		{
			desiredXV = 15;
		}
		if (legDir)
		{
			legAngle += LEG_MULT * AllegroExt::Core::rate;
			if (legAngle > 20)
			{
				legDir = false;
			}
		}
		else
		{
			legAngle -= LEG_MULT * AllegroExt::Core::rate;
			if (legAngle < -20)
			{
				legDir = true;
			}
		}
		if (stepSoundTimer <= 0 && onPlatform)
		{
			stepSoundTimer = 30;
			srand(time(NULL));
			int soundType = rand() % 3;
			if (soundType == 0)
			{
				grass1->play(.45);
			}
			else if (soundType == 1)
			{
				grass2->play(.45);
			}
			else if (soundType == 2)
			{
				grass3->play(.45);
			}
		}
	}
	if (desiredXV == 0)
	{
		if (legAngle > 0)
		{
			legAngle -= LEG_MULT * 2 * AllegroExt::Core::rate;
			if (legAngle < 0)
			{
				legAngle = 0;
			}
		}
		else if (legAngle < 0)
		{
			legAngle += LEG_MULT * 2 * AllegroExt::Core::rate;
			if (legAngle > 0)
			{
				legAngle = 0;
			}
		}
	}
	desiredXV += platformVX;
	float deltaXV = desiredXV - vel.x;
	float xImpulse = physBody->getBody()->GetMass() * deltaXV;
	float yImpulse = 0;
	if (jumpTimer < 20)
	{
		jumpTimer += AllegroExt::Core::rate;
	}
	if (AllegroExt::Input::InputManager::keyPressed('w') && !movementDisabled && !isDead())
	{
		physBody->getBody()->SetAwake(true);
		if (onPlatform && jumpTimer >= 20)
		{
			jumpTimer = 0;
			yImpulse = physBody->getBody()->GetMass() * JUMP_FORCE;
		}
	}
	if ((xImpulse != 0 || yImpulse != 0))
	{
		physBody->getBody()->ApplyLinearImpulse(b2Vec2(xImpulse, yImpulse), physBody->getBody()->GetWorldCenter(), true);
	}
	if (!isDead())
	{
		float angle = atan2(-(AllegroExt::Input::InputManager::mouseY - STANDARD_HEIGHT / 2) - 63, AllegroExt::Input::InputManager::mouseX - STANDARD_WIDTH / 2);
		if (angle < 0)
		{
			angle += M_PI * 2;
		}
		float gXOff = cos(-angle) * GUN_OFF_PAR;
		float gYOff = sin(-angle) * GUN_OFF_PAR;
		if (angle <= M_PI / 2 || angle >= (3 * M_PI) / 2)
		{
			float tanAngle = angle + M_PI / 2;
			gXOff += cos(-tanAngle * GUN_OFF_PERP);
			gYOff += sin(-tanAngle * GUN_OFF_PERP);
		}
		else
		{
			float tanAngle = angle - M_PI / 2;
			gXOff += cos(-tanAngle * GUN_OFF_PERP);
			gYOff += sin(-tanAngle * GUN_OFF_PERP);
		}
		flashLight->setXY(gunImg->getX(), gunImg->getY());
		flashLight->setRads(-angle);
		topArm->rotate(-angle - M_PI / 2);
		topForearm->rotate(-angle - M_PI / 2);
		gunImg->rotate(-angle - M_PI / 2);
		float gunX = gunImg->getX() / B2D_SCALE + world->getMeterWorldX() + gXOff;
		float gunY = (-gunImg->getY()) / B2D_SCALE + world->getMeterWorldY() - gYOff;
		gun->draw(gunX, gunY, angle);
		if (AllegroExt::Input::InputManager::getClicked() > 0 && !movementDisabled)
		{
			gun->shoot(gunX, gunY, angle);
		}
		topLeg->rotateDegs(legAngle);
		bottomLeg->rotateDegs(-legAngle);
		if (angle <= M_PI / 2 || angle >= (3 * M_PI) / 2)
		{
			if (horzFlip)
			{
				topArm->setFlip(false, false);
				topForearm->setFlip(false, false);
				torso->setFlip(false, false);
				topLeg->setFlip(false, false);
				bottomLeg->setFlip(false, false);
				gunImg->setFlip(false, false);
				horzFlip = false;
			}
		}
		else
		{
			if (!horzFlip)
			{
				topArm->setFlip(true, false);
				topForearm->setFlip(true, false);
				torso->setFlip(true, false);
				topLeg->setFlip(true, false);
				bottomLeg->setFlip(true, false);
				gunImg->setFlip(true, false);
				horzFlip = true;
			}
		}
		if (AllegroExt::Input::InputManager::keyPressed('e'))
		{
			dig();
		}
	}
	else
	{
		topForearm->rotate(0 + torso->getRads());
		topArm->rotate(0 + torso->getRads());
		gunImg->rotate(0 + torso->getRads());
		flashLight->setXY(gunImg->getX(), gunImg->getY());
		flashLight->setRads(gunImg->getRads());
		if (topLeg->getDegs() < 90)
		{
			topLeg->changeDegs(2 * AllegroExt::Core::rate);
		}
		if (bottomLeg->getDegs() < 90)
		{
			bottomLeg->changeDegs(2 * AllegroExt::Core::rate);
		}
		if (torso->getDegs() < 90)
		{
			torso->changeDegs(1 * AllegroExt::Core::rate);
		}
		torso->setXY(STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2 + bottomLeg->getDegs() / 1.6);
	}
	bottomLeg->draw();
	topLeg->draw();
	torso->draw();
	gunImg->draw();
	topForearm->draw();
	topArm->draw();
}

void Farmer::dig()
{	
	if (currentPlatform != nullptr)
	{
		for (int i = 0; i < currentPlatform->getDigSites().size(); i++)
		{
			float dsX = currentPlatform->getMX() + currentPlatform->getDigSites().at(i)->getOffMX();
			float dsY = currentPlatform->getMY() - currentPlatform->getMH() / 2 - DigSite::DIGSITE_H;
			if (!currentPlatform->getDigSites().at(i)->isDug() && physBody->getX() > dsX - DIG_OFF && physBody->getX() < dsX + DigSite::DIGSITE_W + DIG_OFF)
			{
				int rGen = rand() % 2;
				if (rGen == 0)
				{
					world->getHUD()->addItem(new MedKit());
				}
				else
				{
					world->getHUD()->addItem(new MedShot());
				}
				currentPlatform->getDigSites().at(i)->setAsDug();
			}
		}
	}
}

Farmer::~Farmer()
{
	//delete surroundLight;
	//surroundLight = nullptr;
}
