#include "World.h"
#include "ContactListener.h"
#include "DebugDrawer.h"
#include "RayCaster.h"
#include "Platform.h"
#include "Farmer.h"
#include "PotatoMan.h"
#include "Bullet.h"
#include "BackgroundManager.h"
#include "HUD.h"
#include "MedKit.h"
#include "PhysicsBody.h"
#include "Elevator.h"
#include <ShapeRenderer.h>
#include "PlatLight.h"
#include <InputManager.h>
#include <Core.h>
#include <GaussianBlurrer.h>

using namespace lighting;

World::World()
	:worldX(0), worldY(0), debugDrawer(nullptr), debugDrawEnabled(false), deadMsgAlpha(0), finished(false), finishedAlpha(0)
{ 
	lightLayer = new lighting::LightLayer(STANDARD_WIDTH, STANDARD_HEIGHT, .25);
	GaussianKernelData kernData(36, 9);
	new GaussianBlurrer(lightLayer, kernData, "VertShader.hlsl", "XFragShader.hlsl", "YFragShader.hlsl");
	new GaussianBlurrer(lightLayer, kernData, "VertShader.hlsl", "XFragShader.hlsl", "YFragShader.hlsl");
	contactListener = new ContactListener(this);
	b2Vec2 gravVec(GRAV_X, GRAV_Y);
	physWorld = new b2World(gravVec);
	physWorld->SetContactListener(contactListener);
	farmer = new Farmer(this, (STANDARD_WIDTH / 2) / B2D_SCALE, (STANDARD_HEIGHT / 2) / B2D_SCALE);
	rayCaster = new RayCaster();
	bgm = new BackgroundManager();
	Platform* platform1 = new Platform(this, 90, 0, 20, 2);
	platform1->addDigSite(0);
	platforms.push_back(platform1);
	platforms.push_back(new Platform(this, 20, 2, std::make_pair(50, 10), std::make_pair(80, 10), 3, false));
	platform1 = new Platform(this, 5, 2, std::make_pair(120, 0), std::make_pair(180, 0), 10, true);
	CircleLightSource* circLS = new CircleLightSource(lightLayer, 200, 0, 0, 255);
	platform1->addPlatLight(new PlatLight(circLS, 0 * B2D_SCALE, -3 * B2D_SCALE, "post1.png", 50, 3.3 * B2D_SCALE));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 25, 2, std::make_pair(140, -12), std::make_pair(180, -12), 6, true);
	circLS = new CircleLightSource(lightLayer, 300, 255, 0, 0);
	platform1->addPlatLight(new PlatLight(circLS, -3 * B2D_SCALE, -3 * B2D_SCALE, "post2.png", 30, 3.3 * B2D_SCALE));
	circLS = new CircleLightSource(lightLayer, 300, 0, 255, 0);
	platform1->addPlatLight(new PlatLight(circLS, 3 * B2D_SCALE, -3 * B2D_SCALE, "post2.png", 30, 3.3 * B2D_SCALE));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 6, 1, std::make_pair(196, -14), std::make_pair(196, -42), 6, false);
	circLS = new CircleLightSource(lightLayer, 300, 0, 0, 255);
	platform1->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post1.png", 30, B2D_SCALE * 3.3));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 211, -40, 20, 2);
	platforms.push_back(platform1);
	platform1 = new Platform(this, 234, -42, 6, 2);
	circLS = new CircleLightSource(lightLayer, 500, 200, 200, 200);
	platform1->addPlatLight(new PlatLight(circLS, 0, 3 * B2D_SCALE, "lamp3.png", 30, 3.3 * B2D_SCALE, true));
	platforms.push_back(platform1);
	platforms.push_back(new Platform(this, 246, -36, 6, 2));
	platforms.push_back(new Platform(this, 260, -45, 6, 2));
	platform1 = new Platform(this, 6, 2, std::make_pair(282, -40), std::make_pair(282, -90), 8, false);
	circLS = new CircleLightSource(lightLayer, 300, 255, 0, 0);
	platform1->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post2.png", 30, B2D_SCALE * 3.3));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 250, -60, 40, 2);
	platform1->addDigSite(0);
	platforms.push_back(platform1);
	platforms.push_back(new Platform(this, 278, -55, 1, 20));
	platforms.push_back(new Platform(this, 288, -55, 1, 20));
	platforms.push_back(new Platform(this, 6, 2, std::make_pair(274, -60), std::make_pair(274, -70), 2, true));
	platforms.push_back(new Platform(this, 300, -60, 20, 2));
	platforms.push_back(new Platform(this, 255, -80, 10, 2));
	platforms.push_back(new Platform(this, 280, -100, 40, 2));
	platform1 = new Platform(this, 10, 2, std::make_pair(308, -100), std::make_pair(500, 0), 8, true);
	circLS = new CircleLightSource(lightLayer, 230, 0, 0, 255);
	platform1->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post1.png", 30, 3.3 * B2D_SCALE));
	circLS = new CircleLightSource(lightLayer, 230, 0, 255, 0);
	platform1->addPlatLight(new PlatLight(circLS, 0, 3 * B2D_SCALE, "lamp3.png", 30, 3.3 * B2D_SCALE, true));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 10, 2, std::make_pair(380, -45), std::make_pair(400, -30), 5, false);
	circLS = new CircleLightSource(lightLayer, 200, 0, 255, 0);
	platform1->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post1.png", 30, 3.3 * B2D_SCALE));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 525, -5, 30, 2);
	circLS = new CircleLightSource(lightLayer, 400, 255, 0, 0);
	platform1->addPlatLight(new PlatLight(circLS, 0, -3 * B2D_SCALE, "post2.png", 30, 3.3 * B2D_SCALE));
	platforms.push_back(platform1);
	platform1 = new Platform(this, 560, -15, 20, 2);
	platforms.push_back(platform1);
	potatoMen.push_back(new PotatoMan(this, 140, 20));
	potatoMen.push_back(new PotatoMan(this, 254, -70));
	potatoMen.push_back(new PotatoMan(this, 250, -50));
	potatoMen.push_back(new PotatoMan(this, 527, 10));
	potatoMen.push_back(new PotatoMan(this, 300, -50));
	potatoMen.push_back(new PotatoMan(this, 379, -38));
	elevator = new Elevator(this, 582, -15);
	AllegroExt::Core::GetSoundManager()->addIDVol(1, 0);
	AllegroExt::Core::GetSoundManager()->addIDVol(0, 1);
	hud = new HUD(farmer);
	hud->addItem(new MedKit());
	deadMsg = new AllegroExt::Graphics::ScreenText();
	deadSound = new AllegroExt::Sound::SoundEffect(AllegroExt::Core::GetSoundManager(), "dead.ogg", -1);
	victoryMusic = new AllegroExt::Sound::Music(AllegroExt::Core::GetSoundManager(), "victory.ogg");
}

void World::draw()
{
	bgm->draw(worldX, worldY);
	if (AllegroExt::Input::InputManager::keyTyped('p'))
	{
		setDebugDraw(!debugDrawEnabled);
	}
	if (debugDrawEnabled)
	{
		physWorld->DrawDebugData();
	}
	farmer->draw();
	worldX += farmer->getTransX() * B2D_SCALE;
	worldY -= farmer->getTransY() * B2D_SCALE;
	for (auto it = platforms.begin(); it != platforms.end(); it++)
	{
		(*it)->draw();
	}
	elevator->draw();
	for (auto it = potatoMen.begin(); it != potatoMen.end();)
	{
		(*it)->draw();
		if ((*it)->isDead())
		{
			delete (*it);
			potatoMen.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		(*it)->draw();
		if ((*it)->isFinished())
		{
			delete (*it);
			*it = nullptr;
			bullets.erase(it);
		}
		it++;
	}
	ALLEGRO_BITMAP* prevBitmap = al_get_target_bitmap();
	al_set_target_bitmap(lightLayer->getLightMap());
	for (auto it = bullets.begin(); it != bullets.end(); it++)
	{
		(*it)->drawLight();
	}
	if (farmer->isDead())
	{
		if (deadMsgAlpha == 0)
		{
			deadSound->play();
		}
		if (deadMsgAlpha < 255)
		{
			deadMsgAlpha += AllegroExt::Core::rate * 2;
			if (deadMsgAlpha > 255)
			{
				deadMsgAlpha = 255;
			}
		}
		deadMsg->drawCenteredText("DEAD", STANDARD_WIDTH / 8, STANDARD_HEIGHT / 8 - 80, 160, 255, 0, 0, deadMsgAlpha);
	}
	else
	{
		if (farmer->getBody()->getY() < MIN_Y)
		{
			farmer->damage(1000);
		}
	}
	al_set_target_bitmap(prevBitmap);
	lightLayer->detach();
	lightLayer->draw();
	if (isFinished())
	{
		if (finishedAlpha == 0)
		{
			farmer->setMovementDisabled(true);
			victoryMusic->play();
		}
		if (finishedAlpha < 255)
		{
			finishedAlpha += AllegroExt::Core::rate / 2.0;
		}
		if (finishedAlpha > 255)
		{
			finishedAlpha = 255;
		}
		AllegroExt::Graphics::ShapeRenderer::drawRectangle(0, 0, STANDARD_WIDTH, STANDARD_HEIGHT, 0, 0, 0, finishedAlpha);
		if (finishedAlpha == 255)
		{
			deadMsg->drawCenteredText("VICTORY", STANDARD_WIDTH / 2, STANDARD_HEIGHT / 2, 60, 255, 255, 255, finishedAlpha);
		}
	}
	else if (!farmer->isDead())
	{
		hud->draw();
	}
	physWorld->Step(AllegroExt::Core::rate / 60, 6, 2);
	physWorld->ClearForces();
	if (AllegroExt::Input::InputManager::keyPressed('l'))
	{
		exit(0);
	}
}

int World::rayCast(b2Vec2& p1, b2Vec2& p2, int exceptionGID)
{
	rayCaster->initCast(exceptionGID);
	physWorld->RayCast(rayCaster, p1, p2);
	return rayCaster->getContactGroupID();
}

bool World::isFinished()
{
	if (!finished && elevator->isFinished())
	{
		finished = true;
	}
	return finished;
}

void World::setDebugDraw(bool mode)
{
	this->debugDrawEnabled = mode;
	if (mode == true && debugDrawer == nullptr)
	{
		debugDrawer = new DebugDrawer(this);
		debugDrawer->SetFlags(DebugDraw::e_shapeBit);
		physWorld->SetDebugDraw(debugDrawer);
	}
}
 
World::~World()
{
	for (auto it = platforms.begin(); it != platforms.end(); it++)
	{
		delete (*it);
	}
	platforms.clear();
	physWorld->SetContactListener(nullptr);
	delete contactListener;
	contactListener = nullptr;
	physWorld->SetDebugDraw(nullptr);
	delete debugDrawer;
	debugDrawer = nullptr;
	delete physWorld;
	physWorld = nullptr;
	delete farmer;
	farmer = nullptr;
	delete lightLayer;
	lightLayer = nullptr;
}
