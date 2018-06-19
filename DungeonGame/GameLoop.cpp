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

	//font
	font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);
	entities.push_back(knight);

	lastUpdate = SDL_GetTicks();

	//load music
	dungeonMusic = Mix_LoadMUS("assets/dungeon.wav");
	if (dungeonMusic == NULL) {
		cout << "Music failed to load!!!" << endl;
		SDL_Quit();
		system("pause");
	}

	Mix_PlayMusic(dungeonMusic, -1);
}

GameLoop::~GameLoop()
{
	knight = NULL;
	delete knight;
	font = NULL;
	delete font;
}

//Dans Shit _________________________________________
SDL_Rect sourceRectangle;
SDL_Rect destinationRectangle;
//___________________________________________________

int GameLoop::runGameLoop(SDL_Renderer* renderer)
{
	//Game World Array setup
	srand(time(NULL)); //random seed

	int dungeon[ROW][COLUMN]; //create 2D array

	DungeonGenerator dungeonGenerator;
	EventSystem eventSystem;
	Timer timer;

	SDL_Event e;
	
	while (gameRunning)
	{
		floorRunning = true;
		dungeonGenerator.fillDungeon(dungeon); //reset the dungeon to be generated again

		dungeonGenerator.generateDungeon(dungeon, floor);
		dungeonGenerator.printDungeon(dungeon);

		//generate spawn position
		for (int x = 0; x < 40; x++)
		{
			for (int y = 0; y < 40; y++)
			{
				if (dungeon[y][x] == 8)
				{
					arrayPosX = x;
					arrayPosY = y;
					spawnPosX = x * 32;
					spawnPosY = y * 32 - ((arrayPosY-8) * 32);
				}
			}
		}
		//set player position to spawn position
		knight->pos.x = spawnPosX - playerOffSetX;
		knight->pos.y = spawnPosY - playerOffSetY;

		while (floorRunning && !knight->checkIfDead())
		{

			//draw map
			displayMap(renderer, dungeon);

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

				if (e.type == SDL_KEYDOWN && !timer.isStarted())
				{
					//back to menu screen
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						knight->setHpChange(5000);
					}
					//move to the left
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						//move the actual array position
						arrayPosX -= 1;
						timer.start();
						cout << "current array " << dungeon[arrayPosY][arrayPosX] << endl;
						//check if current array is not 0 (not a block texture)
						if (dungeon[arrayPosY][arrayPosX] != 0)
						{
							knight->pos.x = (arrayPosX * 32) - playerOffSetX;
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
						timer.start();
						cout << "current array " << dungeon[arrayPosX][arrayPosY] << endl;
						//check if current array is not 0 (not a block texture)
						if (dungeon[arrayPosY][arrayPosX] != 0)
						{
							knight->pos.x = (arrayPosX * 32) - playerOffSetX;
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
						timer.start();
						cout << "current array " << dungeon[arrayPosY][arrayPosX] << endl;
						//check if current array is not 0 (not a block texture)
						if (dungeon[arrayPosY][arrayPosX] != 0)
						{
							knight->pos.y = (arrayPosY * 32 - ((arrayPosY-8) * 32)) - playerOffSetY;
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
						timer.start();
						cout << "current array " << dungeon[arrayPosY][arrayPosX] << endl;
						//check if current array is not 0 (not a block texture)
						if (dungeon[arrayPosY][arrayPosX] != 0)
						{
							knight->pos.y = (arrayPosY * 32 - ((arrayPosY-8) * 32 )) - playerOffSetY;
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

			if (timer.isStarted() && (timer.getTicks() >= 200))
			{
				timer.stop();
				//display UI
				displayUI(renderer, knight, floor);
				//check number on array tile and fire respective event
				eventSystem.checkEvent(arrayPosY, arrayPosX, dungeon, renderer, knight, floor, dungeonMusic);

				//check to see if player is at exit
				if (dungeon[arrayPosY][arrayPosX] == 9)
				{
					floorRunning = false;
				}
			}
			else
			{
				//display UI
				displayUI(renderer, knight, floor);
			}

			//check if level up
			if (knight->getExperience() >= knight->getLevelUpExperience())
			{
				knight->levelUp(renderer);
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

		else if (floor == 3 && dungeon[arrayPosY][arrayPosX] == 9)	//if player is on floor 3 and on the exit end game FOR NOW!
		{
			endGameScreen victory;
			victory.getVictory(renderer);
			Mix_FreeMusic(dungeonMusic);
			gameRunning = false;
		}
		floor++;
	}
	//return current coins if victorius otherwise return 0
	return knight->getCoins();
}

void GameLoop::displayUI(SDL_Renderer* renderer, Player* player, float currentFloor)
{
	//UI BAR
	SDL_Surface* uiBarSurface = IMG_Load("assets/battle/UiBar.png");
	//convert surface to texture 
	SDL_Texture* uiBarTexture = SDL_CreateTextureFromSurface(renderer, uiBarSurface);
	//delete surface properly
	SDL_FreeSurface(uiBarSurface);
	SDL_Rect uiBarDestination;
	uiBarDestination.x = 0;
	uiBarDestination.y = 550;
	SDL_QueryTexture(uiBarTexture, NULL, NULL, &uiBarDestination.w, &uiBarDestination.h);

	//START OF VARIABLE DISPLAY
	stringstream stream;
	string s;

	string level = "Level: ";
	stream << fixed << setprecision(0) << player->getLevel();
	s = stream.str();
	level += s;

	stream.str(string());
	stream.clear();

	string experience = "Experience: ";
	stream << fixed << setprecision(0) << player->getExperience();
	s = stream.str();
	experience += s;

	stream.str(string());
	stream.clear();

	string floor = "Floor: ";
	stream << fixed << setprecision(0) << currentFloor;
	s = stream.str();
	floor += s;

	stream.str(string());
	stream.clear();

	string coins = "Coins: ";
	stream << fixed << setprecision(0) << player->getCoins();
	s = stream.str();
	coins += s;

	stream.str(string());
	stream.clear();

	
	SDL_Color textColor = { 0, 0, 0, 0 };

	if (font)
	{
		// now create a surface from the font
		SDL_Surface* levelSurface = TTF_RenderText_Solid(font, level.c_str(), textColor);
		SDL_Surface* experienceSurface = TTF_RenderText_Solid(font, experience.c_str(), textColor);
		SDL_Surface* floorSurface = TTF_RenderText_Solid(font, floor.c_str(), textColor);
		SDL_Surface* coinsSurface = TTF_RenderText_Solid(font, coins.c_str(), textColor);

		//convert surface to texture
		SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
		SDL_Texture* experienceTexture = SDL_CreateTextureFromSurface(renderer, experienceSurface);
		SDL_Texture* floorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
		SDL_Texture* coinsTexture = SDL_CreateTextureFromSurface(renderer, coinsSurface);

		//delete surface properly
		SDL_FreeSurface(levelSurface);
		SDL_FreeSurface(experienceSurface);
		SDL_FreeSurface(floorSurface);
		SDL_FreeSurface(coinsSurface);

		//text destination
		SDL_Rect levelDestination;
		levelDestination.x = 600;
		levelDestination.y = 560;

		SDL_Rect experienceDestination;
		experienceDestination.x = 900;
		experienceDestination.y = 560;

		SDL_Rect floorDestination;
		floorDestination.x = 600;
		floorDestination.y = 660;

		SDL_Rect coinsDestination;
		coinsDestination.x = 900;
		coinsDestination.y = 660;

		SDL_QueryTexture(levelTexture, NULL, NULL, &levelDestination.w, &levelDestination.h);
		SDL_QueryTexture(experienceTexture, NULL, NULL, &experienceDestination.w, &experienceDestination.h);
		SDL_QueryTexture(floorTexture, NULL, NULL, &floorDestination.w, &floorDestination.h);
		SDL_QueryTexture(coinsTexture, NULL, NULL, &coinsDestination.w, &coinsDestination.h);

		SDL_RenderCopy(renderer, uiBarTexture, NULL, &uiBarDestination);
		SDL_RenderCopy(renderer, levelTexture, NULL, &levelDestination);
		SDL_RenderCopy(renderer, experienceTexture, NULL, &experienceDestination);
		SDL_RenderCopy(renderer, floorTexture, NULL, &floorDestination);
		SDL_RenderCopy(renderer, coinsTexture, NULL, &coinsDestination);

		SDL_DestroyTexture(levelTexture);
		SDL_DestroyTexture(experienceTexture);
		SDL_DestroyTexture(floorTexture);
		SDL_DestroyTexture(coinsTexture);
		SDL_DestroyTexture(uiBarTexture);
	}
}

void GameLoop::displayMap(SDL_Renderer* renderer, int(*dungeon)[40])
{
	//LOAD UP Assets as Surface then convert to texture
	SDL_Surface* grassSurface = IMG_Load("assets/TexturesTest/GrassTile.png");
	SDL_Texture* grassTexture = SDL_CreateTextureFromSurface(renderer, grassSurface);

	SDL_Surface* gateEnteranceSurface = IMG_Load("assets/TexturesTest/GateEnterance.png");
	SDL_Texture* gateEnteranceTexture = SDL_CreateTextureFromSurface(renderer, gateEnteranceSurface);

	SDL_Surface* gateExitSurface = IMG_Load("assets/TexturesTest/GateExit.png");
	SDL_Texture* gateExitTexture = SDL_CreateTextureFromSurface(renderer, gateExitSurface);

	SDL_Surface* blockSurface = IMG_Load("assets/TexturesTest/block.png");
	SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);

	//Free memory by clearing surfaces
	SDL_FreeSurface(grassSurface);
	SDL_FreeSurface(gateEnteranceSurface);
	SDL_FreeSurface(blockSurface);
	SDL_FreeSurface(gateExitSurface);

	//draw tile map in the loop
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (dungeon[y][x] <= 7 && dungeon[y][x] > 1)
			{
				SDL_QueryTexture(grassTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32 - ((arrayPosY - 8) * 32);
				destinationRectangle.w = sourceRectangle.w * 1; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 1; //copy the height of our texture
				SDL_RenderCopy(renderer, grassTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 0)
			{
				SDL_QueryTexture(blockTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32 - ((arrayPosY - 8) * 32);
				destinationRectangle.w = sourceRectangle.w * 1; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 1; //copy the height of our texture
				SDL_RenderCopy(renderer, blockTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 8)
			{

				SDL_QueryTexture(gateExitTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32 - ((arrayPosY - 8) * 32);
				destinationRectangle.w = sourceRectangle.w * 1; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 1; //copy the height of our texture
				SDL_RenderCopy(renderer, gateExitTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 9)
			{

				SDL_QueryTexture(gateEnteranceTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32 - ((arrayPosY - 8) * 32);
				destinationRectangle.w = sourceRectangle.w * 1; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 1; //copy the height of our texture
				SDL_RenderCopy(renderer, gateEnteranceTexture, &sourceRectangle, &destinationRectangle);
			}
		}
	}
	SDL_DestroyTexture(grassTexture);
	SDL_DestroyTexture(gateEnteranceTexture);
	SDL_DestroyTexture(gateExitTexture);
	SDL_DestroyTexture(blockTexture);

}