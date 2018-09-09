#include "MedShot.h"
#include "Farmer.h"

MedShot::MedShot()
	:Item()
{
	id = MEDSHOT_ID;
	texture = new AllegroExt::Graphics::Image("medShot.png");
}

void MedShot::use(Farmer * farmer)
{
	farmer->addHealth(MEDSHOT_HEAL);
}


MedShot::~MedShot()
{
}
