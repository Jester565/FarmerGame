#pragma once
#include "Item.h"
class MedShot : public Item
{
public:
	static const int MEDSHOT_ID = 2;
	static const int MEDSHOT_HEAL = 3;
	MedShot();

	virtual void use(Farmer* farmer);

	~MedShot();
};
