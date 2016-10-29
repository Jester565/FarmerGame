#include "MedKit.h"
#include "Farmer.h"


MedKit::MedKit()
	:Item()
{
	id = MEDKIT_ID;
	texture = new AllegroExt::Graphics::Image("medKit.png");
}

void MedKit::use(Farmer * farmer)
{
	farmer->addHealth(MEDKIT_HEAL);
}

MedKit::~MedKit()
{
}
