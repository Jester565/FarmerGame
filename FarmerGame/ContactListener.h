#pragma once
#include <Box2D/Box2D.h>
#include <map>
#include <iostream>

class World;

class ContactListener : public b2ContactListener
{
public:
	ContactListener(World* world);

	void BeginContact(b2Contact* contact) override;

	void EndContact(b2Contact* contact) override;

	~ContactListener();

private:
	void checkPlatformsBegin(b2Fixture* fixA, b2Fixture* fixB);
	void checkPlatformsEnd(b2Fixture* fixA, b2Fixture* fixB);
	void checkBulletsBegin(b2Fixture* fixA, b2Fixture* fixB);
	void checkBulletsEnd(b2Fixture* fixA, b2Fixture* fixB);
	std::map <int, int> idCounters;
	World* world;
};

