#pragma once
#include <Box2D/Box2D.h>

class World;
class PhysicsBody;

class PhysicsJoint
{
public:
	PhysicsJoint(World* world, PhysicsBody* body1, PhysicsBody* body2, float body1X, float body1Y, float body2X, float body2Y, bool inMeters = false, bool collide = false);
	~PhysicsJoint();

protected:
	World* world;
	b2WeldJoint* joint;
	PhysicsBody* body1;
	PhysicsBody* body2;
};

