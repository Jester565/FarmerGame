#include "GameCore.h"
#include <Windows.h>
#include <iostream>
#include <allegro5/allegro.h>

static const int MAX_WDIR_LENGTH = 100;

int main()
{
	char buffer[MAX_WDIR_LENGTH];
	GetCurrentDirectoryA(MAX_WDIR_LENGTH, buffer);
	std::string resourcePath(buffer);
	std::cout << "WDIR: " << resourcePath << std::endl;
	GameCore* gameCore = new GameCore(resourcePath);
	gameCore->setFPSCap(900);
	gameCore->run();
}