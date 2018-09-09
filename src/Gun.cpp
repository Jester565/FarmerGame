#include "Gun.h"
#include "Bullet.h"
#include "World.h"
#include <Core.h>

Gun::Gun(World* world, const std::string& soundPath, int groupID)
	:world(world), groupID(groupID), timer(0)
{
	bulletColor = al_map_rgb(255, 0, 0);
	soundEffect = new AllegroExt::Sound::SoundEffect(AllegroExt::Core::GetSoundManager(), soundPath, 0);
}

void Gun::setColor(float r, float g, float b)
{
	bulletColor = al_map_rgb_f(r, g, b);
}

void Gun::draw(float x, float y, float angle)
{
	if (timer > 0)
	{
		timer -= AllegroExt::Core::rate;
	}
}

void Gun::shoot(float x, float y, float angle)
{
	if (timer <= 0)
	{
		soundEffect->play();
		world->addBullet(new Bullet(world, x, y, angle, groupID, bulletColor));
		timer = RATE_OF_FIRE;
	}
}

Gun::~Gun()
{
}
