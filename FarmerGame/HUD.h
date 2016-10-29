#pragma once
#include <list>
#include <vector>
#include <ScreenText.h>

class Item;
class Farmer;

class HUD
{
public:
	static const int MAX_INVENTORY_SIZE = 5;
	static const int MAX_STACK_SIZE = 5;
	static const int ITEM_W = 70;
	static const int ITEM_W_OFF = 10;
	static const int HEALTH_W_OFF = 3;
	static const int HEALTH_BAR_W = 100;
	static const int HEALTH_BAR_H = 20;

	HUD(Farmer* farmer);

	bool addItem(Item* item);

	void draw();

	std::vector <AllegroExt::Graphics::ScreenText*> itemNumText;

	~HUD();

private:
	std::list <std::vector<Item*>> items;
	Farmer* farmer;
};

