#include "GameLoop.h"

GameLoop::GameLoop(SDL_Renderer* renderer)
{
	gameRunning = true;
	floorRunning = true;
	floor = 1;

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

	//calulate original experience
	knight->calculateExperienceNeeded();

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

	int dungeon[ROW][COLUMN]; //create 2D array

	BattleLoop battleLoop;
	DungeonGenerator dungeonGenerator;
	EventSystem eventSystem;

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

	SDL_Event e;
	
	while (gameRunning)
	{
		floorRunning = true;
		dungeonGenerator.fillDungeon(dungeon); //reset the dungeon to be generated again

		dungeonGenerator.generateDungeon(dungeon, floor);
		dungeonGenerator.printDungeon(dungeon);

		//generate tile map here
		for (int x = 0; x < 30; x++)
		{
			for (int y = 0; y < 30; y++)
			{
				//2-7 is the walkable grass area
				//0 = unwalkable block 
				//8 = entry gate
				//9 exit gate
				if (dungeon[y][x] <= 7 && dungeon[y][x] > 1)
				{
					//make this array a walkable grass area
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
					//make this array a unwalkable block area
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
					//asign array position x and y
					arrayPosX = x;
					arrayPosY = y;

				}
				if (dungeon[y][x] == 8 || dungeon[y][x] == 9)
				{
					//make 8 and 9 array the gate. 
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

		while (floorRunning && !knight->checkIfDead())
		{
			//draw tile map in the loop
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

			//draw UI over map

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
					//back to menu screen
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						gameRunning = false;
						floorRunning = false;
					}
					//move to the left
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						//move the actual array position
						arrayPosX -= 1;
						//check if current array is not 0 (not a block texture)
						if (arrayPosX != 0)
						{
							knight->pos.x = (arrayPosX * 32) - playerOffSetX;
							cout << "X: " << arrayPosX << endl;
							cout << &dungeon << endl;
						}
						//else if current array position is 0 (a block texture), then move back
						else
						{
							arrayPosX += 1;
						}
					}
					//move to the right
					if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					{
						//move the actual array position
						arrayPosX += 1;
						//check if current array is not 0 (not a block texture)
						if (arrayPosX != 0)
						{
							knight->pos.x = (arrayPosX * 32) - playerOffSetX;
							cout << "X: " << arrayPosX << endl;
							cout << &dungeon << endl;
						}
						//else if current array position is 0 (a block texture), then move back
						else
						{
							arrayPosX -= 1;
						}

					}
					//move up
					if (e.key.keysym.scancode == SDL_SCANCODE_UP)
					{
						//move the actual array position
						arrayPosY -= 1;
						//check if current array is not 0 (not a block texture)
						if (arrayPosY != 0)
						{
							knight->pos.y = (arrayPosY * 32) - playerOffSetY;
							cout << "Y: " << arrayPosY << endl;
							cout << &dungeon << endl;
						}
						//else if current array position is 0 (a block texture), then move back
						else
						{
							arrayPosY += 1;
						}
					}
					//move down
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					{
						//move the actual array position
						arrayPosY += 1;
						//check if current array is not 0 (not a block texture)
						if (arrayPosY != 0)
						{
							knight->pos.y = (arrayPosY * 32) - playerOffSetY;
							cout << "Y: " << arrayPosY << endl;
							cout << &dungeon << endl;
						}
						//else if current array position is 0 (a block texture), then move back
						else
						{
							arrayPosY -= 1;
						}
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

			//if (gameEvent == battle)
			battleLoop.runBattleLoop(renderer, knight);

			//check to see if player is at exit
			if (dungeon[arrayPosX][arrayPosY] == 9)
			{
				floor++;
				floorRunning = false;
			}

			SDL_RenderPresent(renderer);
		}

		//victory or defeat conditions
		if (knight->checkIfDead()) //if player is dead
		{
			endGameScreen gameOver;
			gameOver.getDefeat(renderer);
			knight->setCoins(0);
			gameRunning = false;
		}
		else if (floor == 2 && dungeon[arrayPosX][arrayPosY] == 9)	//if player is on floor 2 and on the exit end game FOR NOW!
		{
			endGameScreen victory;
			victory.getVictory(renderer);
			gameRunning = false;
		}
	}
	//return current coins if victorius otherwise return 0
	return knight->getCoins();
}

