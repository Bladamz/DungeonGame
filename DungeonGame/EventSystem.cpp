#include "EventSystem.h"

EventSystem::EventSystem()
{
	srand(time(NULL));
	eventExperience = 0;
	eventRunning = false;
	eventMessage = "";
}

float EventSystem::experienceEvent(SDL_Renderer* renderer)
{
	eventRunning = true;
	eventExperience == rand() % 400 + 1;

	eventMessage = "You stumble across an old book, on tonights camp you decided to skim through a few pages.\n You have gained ";
	eventMessage += eventExperience;
	eventMessage += " experience";
	const char * cMessage = new char();
	cMessage = eventMessage.c_str();

	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(exitButtonSurface);

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);	//params: font file, font size
	SDL_Color textColor = { 255, 255,255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* eventMessageSurface = TTF_RenderText_Blended(font, cMessage, textColor);

	//convert surface to texture
	SDL_Texture* eventMessageTexure = SDL_CreateTextureFromSurface(renderer, eventMessageSurface);

	//delete surface properly
	SDL_FreeSurface(eventMessageSurface);

	//text destination
	SDL_Rect eventMessageDestination;
	eventMessageDestination.x = 1280;
	eventMessageDestination.y = 50;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(eventMessageTexure, NULL, NULL, &eventMessageDestination.w, &eventMessageDestination.h);

	SDL_Event e;

	while (eventRunning)
	{
		//place UI elements
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 620 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);
		//place start and back button
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonDestination);

		//place text
		SDL_RenderCopy(renderer, eventMessageTexure, NULL, &eventMessageDestination);

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						eventRunning = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	delete(cMessage);
	return eventExperience;
}

float EventSystem::coinEvent(SDL_Renderer* renderer)
{
	eventRunning = true;
	eventCoins == rand() % 500 + 1;

	eventMessage = "In the distance you spot something unusual, as you approach it you\n realise its a small pouch of coins.You received ";
	eventMessage += eventCoins;
	eventMessage += " coins";
	const char * cMessage = new char();
	cMessage = eventMessage.c_str();

	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(exitButtonSurface);

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);	//params: font file, font size
	SDL_Color textColor = { 255, 255,255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* eventMessageSurface = TTF_RenderText_Blended(font, cMessage , textColor);

	//convert surface to texture
	SDL_Texture* eventMessageTexure = SDL_CreateTextureFromSurface(renderer, eventMessageSurface);

	//delete surface properly
	SDL_FreeSurface(eventMessageSurface);

	//text destination
	SDL_Rect eventMessageDestination;
	eventMessageDestination.x = 1280;
	eventMessageDestination.y = 50;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(eventMessageTexure, NULL, NULL, &eventMessageDestination.w, &eventMessageDestination.h);

	SDL_Event e;

	while (eventRunning)
	{
		//place UI elements
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 620 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);
		//place start and back button
		SDL_RenderCopy(renderer, exitButtonTexture, NULL, &exitButtonDestination);

		//place text
		SDL_RenderCopy(renderer, eventMessageTexure, NULL, &eventMessageDestination);

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						eventRunning = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	delete(cMessage);
	return eventCoins;
}