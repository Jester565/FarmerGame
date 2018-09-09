#include "BackgroundManager.h"
#include <Core.h>
#include <allegro5/allegro.h>

const std::string BackgroundManager::ImgPath = "dirt.png";

BackgroundManager::BackgroundManager()
{
	bmp = al_load_bitmap(ImgPath.c_str());
	imgW = al_get_bitmap_width(bmp);
}

void BackgroundManager::draw(int wX, int wY)
{
	al_hold_bitmap_drawing(true);
	int x = -(wX % imgW);
	if (wX < 0)
	{
		x = -(imgW + wX % imgW);
	}
	while (x < STANDARD_WIDTH)
	{
		int y = -(wY % imgW);
		if (wY < 0)
		{
			y = -(imgW + wY % imgW);
		}
		while (y < STANDARD_HEIGHT)
		{
			al_draw_bitmap(bmp, x, y, NULL);
			y += imgW;
		}
		x += imgW;
	}
	al_hold_bitmap_drawing(false);
}

BackgroundManager::~BackgroundManager()
{
	al_destroy_bitmap(bmp);
	bmp = nullptr;
}
