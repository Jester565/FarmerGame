#include "RayCaster.h"



RayCaster::RayCaster()
{
	initCast(0);
}

float32 RayCaster::ReportFixture(b2Fixture * fixture, const b2Vec2 & point, const b2Vec2 & normal, float32 fraction)
{
	int groupID = fixture->GetFilterData().groupIndex;
	if (groupID == exceptionGroupID)
	{
		return 1;
	}
	contactGroupID = groupID;
	return fraction;
}

RayCaster::~RayCaster()
{
}
