#pragma once
#include "Item.h"

class MedKit : public Item
{
public:
	static const int MEDKIT_ID = 1;
	static const int MEDKIT_HEAL = 4;
	MedKit();

	virtual void use(Farmer* farmer);

	~MedKit();
};

