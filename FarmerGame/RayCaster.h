#pragma once
#include <Box2D/Box2D.h>

class RayCaster : public b2RayCastCallback
{
public:
	RayCaster();

	void initCast(int exceptionGID)
	{
		this->exceptionGroupID = exceptionGID;
		contactGroupID = 0;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	int getContactGroupID()
	{
		return contactGroupID;
	}

	~RayCaster();

private:
	int exceptionGroupID;
	int contactGroupID;
};

