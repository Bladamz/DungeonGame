#include "GameLoop.h"

GameLoop::GameLoop()
{
	gameRunning = true;
	floor = 1;
	currentCoins = 0;
}

GameLoop::~GameLoop()
{
}

int GameLoop::runGameLoop(SDL_Renderer* renderer)
{
	//Game World Array setup
	srand(time(NULL)); //random seed

	int dungeon[ROW][COLUMN]; //create array

	BattleLoop battleLoop;
	DungeonGenerator dungeonGenerator;

	dungeonGenerator.fillDungeon(dungeon); //reset the dungeon to be generated again

	dungeonGenerator.generateDungeon(dungeon, floor);
	dungeonGenerator.printDungeon(dungeon);

	//init tile map
	
	//load art

	while (gameRunning)
	{
		//run through tile map
		//draw tile map
		
		//draw UI over map
		
		//draw character on tile they are standing on


		//input handler 
		//movement is WASD OR UP/DOWN/LEFT/RIGHT
		//mouse button down click on menu button OR UI Elements

		//if (gameEvent == battle)
		battleLoop.runBattleLoop(renderer);
		//if player wins or loses
			//display victory screen with currentCoins
			//display defeat screen and forget all scores


		//SDL_RenderPresent(renderer);
		gameRunning = false;
	}
	//return current coins if victorius otherwise return 0
	return currentCoins;
}
