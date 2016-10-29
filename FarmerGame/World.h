#pragma once
#include <Box2D/Box2D.h>
#include <DisplayManager.h>
#include <ScreenText.h>
#include <Music.h>
#include <SoundEffect.h>
#include <LightLayer.h>
#include <vector>
#include <list>

static const float B2D_SCALE = 19;
static const float GRAV_Y = -40;
static const float GRAV_X = 0;
static const int MIN_Y = -150;

class PotatoMan;
class Platform;
class ContactListener;
class DebugDrawer;
class Farmer;
class Bullet;
class RayCaster;
class BackgroundManager;
class HUD;
class Elevator;

class World
{
public:
	World();

	b2World* getPhysWorld()
	{
		return physWorld;
	}

	void draw();

	int rayCast(b2Vec2& p1, b2Vec2& p2, int exceptionGID);

	float getPixelWorldX()
	{
		return worldX;
	}

	float getPixelWorldY()
	{
		return worldY;
	}

	float getMeterWorldX()
	{
		return worldX / B2D_SCALE;
	}

	bool isFinished();

	float getMeterWorldY()
	{
		return (-worldY + STANDARD_HEIGHT) / B2D_SCALE;
	}

	ContactListener* getContactListener()
	{
		return contactListener;
	}

	std::vector <Platform*>* getPlatforms()
	{
		return &platforms;
	}

	Farmer* getFarmer()
	{
		return farmer;
	}

	RayCaster* getRayCaster()
	{
		return rayCaster;
	}

	void setDebugDraw(bool mode);

	void addBullet(Bullet* bullet)
	{
		bullets.push_back(bullet);
	}

	lighting::LightLayer* getLightLayer()
	{
		return lightLayer;
	}

	HUD* getHUD()
	{
		return hud;
	}

	~World();

private:
	float finishedAlpha;
	float worldX;
	float worldY;
	float deadMsgAlpha;
	bool debugDrawEnabled;
	Elevator* elevator;
	lighting::LightLayer* lightLayer;
	BackgroundManager* bgm;
	RayCaster* rayCaster;
	Farmer* farmer;
	b2World* physWorld;
	ContactListener* contactListener;
	DebugDrawer* debugDrawer;
	std::list <Bullet*> bullets;
	std::vector <Platform*> platforms;
	std::vector <PotatoMan*> potatoMen;
	AllegroExt::Graphics::ScreenText* deadMsg;
	AllegroExt::Sound::Music* victoryMusic;
	AllegroExt::Sound::SoundEffect* deadSound;
	HUD* hud;
	bool finished;
};

