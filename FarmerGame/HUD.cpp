#include "HUD.h"
#include "Item.h"
#include "Farmer.h"
#include <ShapeRenderer.h>
#include <InputManager.h>
#include <Core.h>

HUD::HUD(Farmer* farmer)
	:farmer(farmer)
{
	for (int i = 0; i < MAX_INVENTORY_SIZE; i++)
	{
		itemNumText.push_back(new AllegroExt::Graphics::ScreenText());
	}
}

bool HUD::addItem(Item * item)
{
	auto itemIter = items.begin();
	for (; itemIter != items.end(); itemIter++)
	{
		if (itemIter->at(0)->getID() == item->getID())
		{
			if (itemIter->size() < MAX_STACK_SIZE)
			{
				itemIter->push_back(item);
				return true;
			}
			return false;
		}
	}
	if (items.size() < MAX_INVENTORY_SIZE)
	{
		std::vector<Item*> idVec({ item });
		items.push_back(idVec);
		return true;
	}
	return false;
}

void HUD::draw()
{
	int i = 0;
	float x = STANDARD_WIDTH / 2 - (ITEM_W * 1.2) * (MAX_INVENTORY_SIZE / 2.0);
	float y = 20;
	for (auto it = items.begin(); it != items.end(); it++)
	{
		AllegroExt::Graphics::ShapeRenderer::drawRectangle(x, y, ITEM_W, ITEM_W, 200, 200, 200, 10);
		it->at(0)->draw(x + ITEM_W_OFF, y + ITEM_W_OFF, ITEM_W - ITEM_W_OFF * 2, ITEM_W - ITEM_W_OFF * 2);
		itemNumText.at(i)->drawText(std::to_string(it->size()), x, y, 20, 0, 0, 0, 255);
		char c = std::to_string(i + 1).at(0);
		if (AllegroExt::Input::InputManager::keyTyped(c))
		{
			it->at(it->size() - 1)->use(farmer);
			delete it->at(it->size() - 1);
			it->pop_back();
			if (it->size() == 0)
			{
				items.erase(it);
				it--;
			}
		}
		i++;
		x += ITEM_W * 1.2;
	}
	while (i < MAX_INVENTORY_SIZE)
	{
		AllegroExt::Graphics::ShapeRenderer::drawRectangle(x, y, ITEM_W, ITEM_W, 200, 200, 200, 10);
		i++;
		x += ITEM_W * 1.2;
	}
	float hbX = 20;
	float hbY = STANDARD_HEIGHT - HEALTH_BAR_H - 20;
	AllegroExt::Graphics::ShapeRenderer::drawRectangle(hbX, hbY, HEALTH_BAR_W, HEALTH_BAR_H, 200, 200, 200, 20);
	AllegroExt::Graphics::ShapeRenderer::drawRectangle(hbX + HEALTH_W_OFF, hbY + HEALTH_W_OFF, ((float)farmer->getHealth() / Farmer::FARMER_MAX_HEALTH) * (HEALTH_BAR_W - HEALTH_W_OFF * 2), HEALTH_BAR_H - HEALTH_W_OFF * 2, 255, 0, 0, 255);
}


HUD::~HUD()
{
}
 