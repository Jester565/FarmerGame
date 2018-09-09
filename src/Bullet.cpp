#include "Bullet.h"
#include "World.h"
#include "PhysicsBody.h"
#include "Platform.h"
#include "Mover.h"
#include <ShapeRenderer.h>
#include <LightLayer.h>
#include <Core.h>
#include <Box2D/Box2D.h>

const float Bullet::BULLET_SPEED = 50;
const float Bullet::BULLET_W = .3;
const float Bullet::BULLET_H = .3;

Bullet::Bullet(World* world, float mX, float mY, float angle, int groupID, ALLEGRO_COLOR bulletColor)
	:world(world), dis(0), finished(false), bulletColor(bulletColor)
{
	physBody = new PhysicsBody(world, BODY_DYNAM, mX, mY, 0);
	b2FixtureDef playerFixDef;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(BULLET_W / 2, BULLET_H / 2);
	playerFixDef.shape = &boxShape;
	playerFixDef.shape = &boxShape;
	playerFixDef.density = 0;
	playerFixDef.restitution = 0;
	playerFixDef.friction = .9;
	playerFixDef.filter.groupIndex = groupID;
	playerFixDef.userData = (void*)this;
	playerFixDef.filter.categoryBits = Bullet::BULLET_CATEGORY;
	playerFixDef.filter.maskBits = Platform::PLATFORM_CATEGORY | Mover::MOVER_CATEGORY;
	physBody->setFixedRotation(true);
	physBody->getBody()->CreateFixture(&playerFixDef);
	physBody->setW(BULLET_W);
	physBody->setH(BULLET_H);
	physBody->setBmp();
	physBody->getBody()->SetBullet(true);
	vX = cos(angle) * BULLET_SPEED;
	vY = sin(angle) * BULLET_SPEED;
}

void Bullet::drawLight()
{
	double qs = world->getLightLayer()->getLightBmpScale();
	int x = ((physBody->getX() - world->getMeterWorldX()) * B2D_SCALE) * qs;
	int y = (-(physBody->getY() - world->getMeterWorldY()) * B2D_SCALE) * qs;
	AllegroExt::Graphics::ShapeRenderer::drawRectangle(x - 7, y - 7, 14, 14 , bulletColor.r * 255, bulletColor.g * 255, bulletColor.b * 255, bulletColor.a * 255);
}

void Bullet::draw()
{
	dis += abs(BULLET_SPEED * (AllegroExt::Core::rate / AllegroExt::Core::DEFAULT_FPS_CAP));
	if (dis > MAX_DIS)
	{
		finished = true;
	}
	b2Vec2 physVel(vX, vY);
	physBody->getBody()->SetLinearVelocity(physVel);
	int x = ((physBody->getX() - world->getMeterWorldX()) * B2D_SCALE);
	int y = (-(physBody->getY() - world->getMeterWorldY()) * B2D_SCALE);
	AllegroExt::Graphics::ShapeRenderer::drawRectangle(x - 3, y - 3, 6, 6, bulletColor.r * 255, bulletColor.g * 255, bulletColor.b * 255, bulletColor.a * 255);
}

Bullet::~Bullet()
{
	delete physBody;
	physBody = nullptr;
}
