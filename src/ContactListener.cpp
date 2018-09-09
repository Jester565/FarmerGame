#include "ContactListener.h"
#include "World.h"
#include "Platform.h"
#include "Mover.h"
#include "Bullet.h"

ContactListener::ContactListener(World* world)
	:b2ContactListener(), world(world)
{
}

void ContactListener::BeginContact(b2Contact * contact)
{
	checkPlatformsBegin(contact->GetFixtureA(), contact->GetFixtureB());
	checkPlatformsBegin(contact->GetFixtureB(), contact->GetFixtureA());
	checkBulletsBegin(contact->GetFixtureA(), contact->GetFixtureB());
	checkBulletsBegin(contact->GetFixtureB(), contact->GetFixtureA());
}

void ContactListener::EndContact(b2Contact * contact)
{
	checkPlatformsEnd(contact->GetFixtureA(), contact->GetFixtureB());
	checkPlatformsEnd(contact->GetFixtureB(), contact->GetFixtureA());
}

ContactListener::~ContactListener()
{
}

void ContactListener::checkPlatformsBegin(b2Fixture * fixA, b2Fixture * fixB)
{
	if (fixA->GetFilterData().groupIndex == Platform::PLATFORM_GROUP_ID)
	{
		Platform* platform = (Platform*)fixA->GetUserData();
		if (Mover::IsMover(fixB->GetFilterData().categoryBits) && fixB->GetDensity() == 1000)
		{
			Mover* mover = (Mover*)fixB->GetUserData();
			if (mover != nullptr)
			{
				platform->addMover(mover);
			}
		}
	}
}

void ContactListener::checkPlatformsEnd(b2Fixture * fixA, b2Fixture * fixB)
{
	if (fixA->GetFilterData().groupIndex == Platform::PLATFORM_GROUP_ID)
	{
		if (Mover::IsMover(fixB->GetFilterData().categoryBits) && fixB->GetDensity() == 1000)
		{
			Platform* platform = (Platform*)fixA->GetUserData();
			Mover* mover = (Mover*)fixB->GetUserData();
			if (mover != nullptr)
			{
				platform->removeMover(mover);
			}
		}
	}
}

void ContactListener::checkBulletsBegin(b2Fixture * fixA, b2Fixture * fixB)
{
	if (fixA->GetFilterData().categoryBits == Bullet::BULLET_CATEGORY)
	{
		Bullet* bullet = (Bullet*)fixA->GetUserData();
		if (Mover::IsMover(fixB->GetFilterData().categoryBits) && !bullet->isFinished())
		{
			Mover* mover = (Mover*)fixB->GetUserData();
			if (mover != nullptr)
			{
				mover->damage(bullet->getDamage());
				bullet->setFinished();
			}
		}
		else
		{
			bullet->setFinished();
		}
	}
}

void ContactListener::checkBulletsEnd(b2Fixture * fixA, b2Fixture * fixB)
{
}
