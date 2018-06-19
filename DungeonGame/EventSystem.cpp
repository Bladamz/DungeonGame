#include "EventSystem.h"

EventSystem::EventSystem()
{
	srand(time(NULL));
	eventExperience = 0;
	eventRunning = false;
	eventMessage = "";
	font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);
}

EventSystem::~EventSystem()
{
	battleLoop = NULL;
	delete battleLoop;
	font = NULL;
	delete font;
}

float EventSystem::experienceEvent(SDL_Renderer* renderer)
{
	eventRunning = true;
	eventExperience = rand() % 400 + 1;

	stringstream stream;
	string s;

	eventMessage = "You stumble across an old book, on tonights camp you decided to skim through a few pages.\n You have gained ";
	stream << fixed << setprecision(0) << eventExperience;
	s = stream.str();
	eventMessage += s;
	eventMessage += " experience.";

	string pressSpace = "Press Space To Continue...";

	SDL_Color textColor = { 255, 255, 255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* pressSpaceSurface = TTF_RenderText_Blended_Wrapped(font, pressSpace.c_str(), textColor, 1000);
	SDL_Surface* eventMessageSurface = TTF_RenderText_Blended_Wrapped(font, eventMessage.c_str(), textColor, 500);

	//convert surface to texture
	SDL_Texture* eventMessageTexure = SDL_CreateTextureFromSurface(renderer, eventMessageSurface);
	SDL_Texture* pressSpaceTexture = SDL_CreateTextureFromSurface(renderer, pressSpaceSurface);

	//delete surface properly
	SDL_FreeSurface(eventMessageSurface);
	SDL_FreeSurface(pressSpaceSurface);

	//text destination
	SDL_Rect eventMessageDestination;
	eventMessageDestination.x = 200;
	eventMessageDestination.y = 200;

	SDL_Rect pressSpaceDestination;
	pressSpaceDestination.x = 500;
	pressSpaceDestination.y = 400;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(eventMessageTexure, NULL, NULL, &eventMessageDestination.w, &eventMessageDestination.h);
	SDL_QueryTexture(pressSpaceTexture, NULL, NULL, &pressSpaceDestination.w, &pressSpaceDestination.h);

	SDL_Event e;

	while (eventRunning)
	{
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 420 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);

		//place text
		SDL_RenderCopy(renderer, eventMessageTexure, NULL, &eventMessageDestination);
		SDL_RenderCopy(renderer, pressSpaceTexture, NULL, &pressSpaceDestination);

		while (SDL_PollEvent(&e))
		{
			//check for keydown
			if (e.type == SDL_KEYDOWN)
			{
				//check for space bar keypress
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					//press space to close event
					eventRunning = false;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	return eventExperience;
}

float EventSystem::coinEvent(SDL_Renderer* renderer)
{
	eventRunning = true;
	eventCoins = rand() % 500 + 1;

	stringstream stream;
	string s;

	eventMessage = "In the distance you spot something unusual, as you approach it you\n realise its a small pouch of coins.You received ";
	stream << fixed << setprecision(0) << eventCoins;
	s = stream.str();
	eventMessage += s;
	eventMessage += " coins.";

	string pressSpace = "Press Space To Continue...";

	SDL_Color textColor = { 255, 255, 255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* pressSpaceSurface = TTF_RenderText_Blended_Wrapped(font, pressSpace.c_str(), textColor, 1000);
	SDL_Surface* eventMessageSurface = TTF_RenderText_Blended_Wrapped(font, eventMessage.c_str(), textColor, 500);

	//convert surface to texture
	SDL_Texture* eventMessageTexure = SDL_CreateTextureFromSurface(renderer, eventMessageSurface);
	SDL_Texture* pressSpaceTexture = SDL_CreateTextureFromSurface(renderer, pressSpaceSurface);

	//delete surface properly
	SDL_FreeSurface(eventMessageSurface);
	SDL_FreeSurface(pressSpaceSurface);

	//text destination
	SDL_Rect eventMessageDestination;
	eventMessageDestination.x = 200;
	eventMessageDestination.y = 200;

	SDL_Rect pressSpaceDestination;
	pressSpaceDestination.x = 500;
	pressSpaceDestination.y = 400;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(eventMessageTexure, NULL, NULL, &eventMessageDestination.w, &eventMessageDestination.h);
	SDL_QueryTexture(pressSpaceTexture, NULL, NULL, &pressSpaceDestination.w, &pressSpaceDestination.h);

	SDL_Event e;

	while (eventRunning)
	{
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 420 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);

		//place text
		SDL_RenderCopy(renderer, eventMessageTexure, NULL, &eventMessageDestination);
		SDL_RenderCopy(renderer, pressSpaceTexture, NULL, &pressSpaceDestination);

		while (SDL_PollEvent(&e))
		{
			//check for keydown
			if (e.type == SDL_KEYDOWN)
			{
				//check for space bar keypress
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{
					//press space to close event
					eventRunning = false;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	return eventCoins;
}

void EventSystem::checkEvent(int row, int column, int(*a)[40],SDL_Renderer *renderer,Player* player, float floor)
{
	int * eventNumber = new int();
	*eventNumber = a[row][column];
	int tempCoins;

	//Make Cave tiles random numbers which represent events
	//2 Is nothing
	//3 is enemy
	//4 is coins
	//5 is experience
	switch (*eventNumber)
	{
	case 3: 
		battleLoop = new BattleLoop();
		//used to check if player ran
		tempCoins = player->getCoins();
		player->addCoins(battleLoop->runBattleLoop(renderer, player,floor));

		//add experience (will later be replaced with unique experience for each enemy)
		if(player->getCoins() > tempCoins)
			player->addExperience(rand() % 500 + 300);
		//set current tile to 0
		a[row][column] = 2;

		if (!player->checkIfDead())
		{
			//reset players stats
			player->rest();
		}

		//clean up battle loop
		battleLoop = NULL;
		delete battleLoop;
		break;
	case 4:
		//play coin event
		player->addCoins(coinEvent(renderer));
		//set current tile to nothing
		a[row][column] = 2;
		break;
	case 5:
		//play experience event
		player->addExperience(experienceEvent(renderer));
		//set current tile to nothing
		a[row][column] = 2;
		break;
	}
	eventNumber = NULL;
	delete(eventNumber);
}