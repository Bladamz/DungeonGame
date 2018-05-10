#include "GameLoop.h"



GameLoop::GameLoop()
{
}


GameLoop::~GameLoop()
{
}

bool GameLoop::runGameLoop(SDL_Renderer* renderer)
{
	//Game World Array setup
	srand(time(NULL)); //random seed

	int dungeon[ROW][COLUMN]; //create array

	DungeonGenerator dungeonGenerator;

	dungeonGenerator.fillDungeon(dungeon); //reset the dungeon to be generated again

	dungeonGenerator.generateDungeon(dungeon, 4);
	dungeonGenerator.printDungeon(dungeon);

	//init tile map
	
	//load art

	gameExit = true;

	while (gameExit)
	{
		//run through tile map
		//draw tile map
		
		//draw UI over map
		
		//draw character on tile they are standing on

		//if (gameEvent == battle)
			//runBattleLoop(renderer);

		//input handler 
		//movement is WASD OR UP/DOWN/LEFT/RIGHT
		//mouse button down click on menu button OR UI Elements

		//SDL_RenderPresent(renderer);
		gameExit = false;
	}

	return gameExit;
}
