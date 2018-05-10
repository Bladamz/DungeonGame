#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "BattleLoop.h"
#include "DungeonGenerator.h"


class GameLoop
{
public:
	bool gameExit;

	GameLoop();
	~GameLoop();

	bool runGameLoop(SDL_Renderer* renderer);

};

