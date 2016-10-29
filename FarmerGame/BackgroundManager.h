#pragma once
#include <allegro5/bitmap.h>
#include <string>

class BackgroundManager
{
public:
	static const std::string ImgPath;
	BackgroundManager();

	void draw(int wX, int wY);

	~BackgroundManager();

private:
	ALLEGRO_BITMAP* bmp;
	int imgW;
};

