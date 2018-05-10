#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "BattleLoop.h"
#include "DungeonGenerator.h"


class GameLoop
{
public:
	bool gameRunning;
	int dungeon;
	int floor;
	int currentCoins;

	GameLoop();
	~GameLoop();

	int runGameLoop(SDL_Renderer* renderer);

};

