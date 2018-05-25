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

//Dans Shit _________________________________________
SDL_Window* Window;
SDL_Renderer* Renderer;
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

	//Dans Shit _________________________________________________________________________________________________________________________________________
	//map will be 480 x 480
	//need to load 16 x 16 png as separate files to display
	//initiate SDL with the subsystems you want to use ie SDL_INIT_VIDEO
	//we're initaliasing all of them (sound, input, video etc)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialised!!!\n";
		return -1; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialised success!!!\n";
	}

	//NEED TO INIT SDL_Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	Window = SDL_CreateWindow("Map Display", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 960, 960, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);

	if (Window != NULL) {
		cout << "Window created!" << endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	//create renderer to help draw stuff to the screen
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer != NULL)
	{
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer FAILED!" << endl;
		return -1;
	}

	//LOAD UP Assets as Surface then convert to texture
	SDL_Surface* grassSurface = IMG_Load("assets/TexturesTest/GrassTile.png");
	SDL_Texture* grassTexture = SDL_CreateTextureFromSurface(Renderer, grassSurface);

	SDL_Surface* gateSurface = IMG_Load("assets/TexturesTest/enterance.png");
	SDL_Texture* gateTexture = SDL_CreateTextureFromSurface(Renderer, gateSurface);

	SDL_Surface* blockSurface = IMG_Load("assets/TexturesTest/block.png");
	SDL_Texture* blockTexture = SDL_CreateTextureFromSurface(Renderer, blockSurface);

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
				cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(Renderer, grassTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 0)
			{
				SDL_QueryTexture(blockTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(Renderer, blockTexture, &sourceRectangle, &destinationRectangle);
			}
			if (dungeon[y][x] == 8 || dungeon[y][x] == 9)
			{
				SDL_QueryTexture(gateTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
				cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;
				sourceRectangle.x = 0;
				sourceRectangle.y = 0;
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;
				destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
				destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture
				SDL_RenderCopy(Renderer, gateTexture, &sourceRectangle, &destinationRectangle);
			}
		}
	}
	SDL_RenderPresent(Renderer);
	//______________________________________________________________________________________________________________________________________________________________________

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
