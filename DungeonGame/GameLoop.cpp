#include "GameLoop.h"

GameLoop::GameLoop(SDL_Renderer* renderer)
{
	gameRunning = true;
	floor = 1;
	currentCoins = 0;

	//idle animation
	SDL_Surface* knightSurface = IMG_Load("assets/menu/knight.png");
	//convert to texture
	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
	//cleanup surface
	SDL_FreeSurface(knightSurface);

	knightAnimation = new Animation(knightTexture, renderer, 45, 112, 151, 0.05);

	knight = new Player();
	knight->setAnimation(knightAnimation);
	knight->setRenderer(renderer);
	knight->pos.x = 200;
	knight->pos.y = 200;

	//player offset
	playerOffSetX = 8;
	playerOffSetY = 26;

	entities.push_back(knight);

	lastUpdate = SDL_GetTicks();
}

GameLoop::~GameLoop()
{
	delete knight;
}

//Dans Shit _________________________________________
SDL_Texture* Texture;
SDL_Rect sourceRectangle;
SDL_Rect destinationRectangle;
//___________________________________________________

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

	//LOAD UP Assets as Surface then convert to texture
	SDL_Surface* grassSurface = IMG_Load("assets/TexturesTest/GrassTile.png");
	SDL_Texture* grassTexture = SDL_CreateTextureFromSurface(renderer, grassSurface);

	SDL_Surface* gateSurface = IMG_Load("assets/TexturesTest/enterance.png");
	SDL_Texture* gateTexture = SDL_CreateTextureFromSurface(renderer, gateSurface);

	SDL_Surface* blockSurface = IMG_Load("assets/TexturesTest/block.png");
	SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);

	//Free memory by clearing surfaces
	SDL_FreeSurface(grassSurface);
	SDL_FreeSurface(gateSurface);
	SDL_FreeSurface(blockSurface);
	
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y < 30; y++)
		{
			if (dungeon[y][x] <= 7 && dungeon[y][x] > 1)
			{
				SDL_QueryTexture(grassTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(renderer, grassTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 0)
			{
				SDL_QueryTexture(blockTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(renderer, blockTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 8)
				{
					spawnPosX = x * 32;
					spawnPosY = y * 32;
					arrayPosX = x;
					arrayPosY = y;
					
				}
			if (dungeon[y][x] == 8 || dungeon[y][x] == 9)
			{
				
				SDL_QueryTexture(gateTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(renderer, gateTexture, &sourceRectangle, &destinationRectangle);
			}
		}
	}
	//set player position to spawn position
	knight->pos.x = spawnPosX - playerOffSetX;
	knight->pos.y = spawnPosY - playerOffSetY;

	SDL_Event e;

	while (gameRunning)
	{
		//run through tile map
		//draw tile map
		
		//draw UI over map
		
		//draw character on tile they are standing on




		//WHEN PLAYER PRESSES UP, DOWN, LEFT OR RIGHT CHANGE arrayPosX and arrayPosY UNLESS IT GOES INTO THE WALL, IF SO DO NOTHING. READ ARRAY TO SEE ACTION. Set player position to arrayPos




		//update delta time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		dt = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit loop
				gameRunning = false;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					gameRunning = false;
				}
			}
		}

		//update all entities (in this case, we only assigned the knight)
		for (auto e : entities) 
		{
			e->update(dt);
		}

		//draw all entities
		for (auto e : entities)
		{
			e->draw(0.4);
		}

		//movement is WASD OR UP/DOWN/LEFT/RIGHT
		//mouse button down click on menu button OR UI Elements

		//if (gameEvent == battle)
		//battleLoop.runBattleLoop(renderer);
		//if player wins or loses
			//display victory screen with currentCoins
			//display defeat screen and forget all scores


		SDL_RenderPresent(renderer);
		//gameRunning = false;
	}
	//return current coins if victorius otherwise return 0
	return currentCoins;
}

