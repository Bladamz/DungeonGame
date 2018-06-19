#include "endGameScreen.h"

// getVictory();
// getDefeat();

void endGameScreen::getVictory(SDL_Renderer* renderer) {
	//DISPLAY LEADERBOARD OF HIGH SCORES
	//SCORE IS BASED ON HOW MUCH MONEY IS COLLECTED ON A VICTORY RUN (BEAT THE GAME)
	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(exitButtonSurface);

	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = 0;

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 50);	//params: font file, font size

	SDL_Color textColor = { 255, 255,255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* highScoresSurface = TTF_RenderText_Blended(font, "VICTORY!", textColor);
	SDL_Surface* nameTextSurface = TTF_RenderText_Blended(font, "Well Done, You have won the game!", textColor);
	SDL_Surface* scoreTextSurface = TTF_RenderText_Blended(font, ">:-D", textColor);
	//convert surface to texture
	SDL_Texture* highScoresTexture = SDL_CreateTextureFromSurface(renderer, highScoresSurface);
	SDL_Texture* namesTextTexture = SDL_CreateTextureFromSurface(renderer, nameTextSurface);
	SDL_Texture* scoresTextTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);
	//delete surface properly
	SDL_FreeSurface(highScoresSurface);
	SDL_FreeSurface(nameTextSurface);
	SDL_FreeSurface(scoreTextSurface);

	//text destination
	SDL_Rect highScoresDestination;
	highScoresDestination.x = 1280 / 2 - (highScoresSurface->w / 2);
	;	highScoresDestination.y = 50;

	SDL_Rect namesTextDestination;
	namesTextDestination.x = 200;
	namesTextDestination.y = 200;

	SDL_Rect scoresTextDestination;
	scoresTextDestination.x = 200;
	scoresTextDestination.y = 300;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(highScoresTexture, NULL, NULL, &highScoresDestination.w, &highScoresDestination.h);
	SDL_QueryTexture(namesTextTexture, NULL, NULL, &namesTextDestination.w, &namesTextDestination.h);
	SDL_QueryTexture(scoresTextTexture, NULL, NULL, &scoresTextDestination.w, &scoresTextDestination.h);

	SDL_Event e;

	bool displayHighScores = true;

	while (displayHighScores)
	{
		// place background again
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);

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
		SDL_RenderCopy(renderer, highScoresTexture, NULL, &highScoresDestination);
		SDL_RenderCopy(renderer, namesTextTexture, NULL, &namesTextDestination);
		SDL_RenderCopy(renderer, scoresTextTexture, NULL, &scoresTextDestination);

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				displayHighScores = false;
				//SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						displayHighScores = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(exitButtonTexture);
	SDL_DestroyTexture(highScoresTexture);
	SDL_DestroyTexture(namesTextTexture);
	SDL_DestroyTexture(scoresTextTexture);
}

void endGameScreen::getDefeat(SDL_Renderer* renderer) {
	//DISPLAY LEADERBOARD OF HIGH SCORES
	//SCORE IS BASED ON HOW MUCH MONEY IS COLLECTED ON A VICTORY RUN (BEAT THE GAME)
	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	SDL_Surface* exitButtonSurface = IMG_Load("assets/menu/exitButton.png");

	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(exitButtonSurface);

	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = 0;

	//destination of exit button
	SDL_Rect exitButtonDestination;
	exitButtonDestination.x = 80;
	exitButtonDestination.y = 540;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(exitButtonTexture, NULL, NULL, &exitButtonDestination.w, &exitButtonDestination.h);

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 50);	//params: font file, font size

	SDL_Color textColor = { 255, 255,255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* highScoresSurface = TTF_RenderText_Blended(font, "DEFEAT!", textColor);
	SDL_Surface* nameTextSurface = TTF_RenderText_Blended(font, "Well Done, You have lost the game!", textColor);
	SDL_Surface* scoreTextSurface = TTF_RenderText_Blended(font, ">:-D", textColor);
	//convert surface to texture
	SDL_Texture* highScoresTexture = SDL_CreateTextureFromSurface(renderer, highScoresSurface);
	SDL_Texture* namesTextTexture = SDL_CreateTextureFromSurface(renderer, nameTextSurface);
	SDL_Texture* scoresTextTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);
	//delete surface properly
	SDL_FreeSurface(highScoresSurface);
	SDL_FreeSurface(nameTextSurface);
	SDL_FreeSurface(scoreTextSurface);

	//text destination
	SDL_Rect highScoresDestination;
	highScoresDestination.x = 1280 / 2 - (highScoresSurface->w / 2);
	;	highScoresDestination.y = 50;

	SDL_Rect namesTextDestination;
	namesTextDestination.x = 200;
	namesTextDestination.y = 200;

	SDL_Rect scoresTextDestination;
	scoresTextDestination.x = 200;
	scoresTextDestination.y = 300;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(highScoresTexture, NULL, NULL, &highScoresDestination.w, &highScoresDestination.h);
	SDL_QueryTexture(namesTextTexture, NULL, NULL, &namesTextDestination.w, &namesTextDestination.h);
	SDL_QueryTexture(scoresTextTexture, NULL, NULL, &scoresTextDestination.w, &scoresTextDestination.h);

	SDL_Event e;

	bool displayHighScores = true;

	while (displayHighScores)
	{
		// place background again
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);

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
		SDL_RenderCopy(renderer, highScoresTexture, NULL, &highScoresDestination);
		SDL_RenderCopy(renderer, namesTextTexture, NULL, &namesTextDestination);
		SDL_RenderCopy(renderer, scoresTextTexture, NULL, &scoresTextDestination);

		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				displayHighScores = false;
				//SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked no exit button region
					if (e.button.x >= exitButtonDestination.x && e.button.x <= exitButtonDestination.x + 300 && e.button.y >= exitButtonDestination.y && e.button.y <= exitButtonDestination.y + 100)
					{
						//EXIT BUTTON CLOSES MENU
						displayHighScores = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(exitButtonTexture);
	SDL_DestroyTexture(highScoresTexture);
	SDL_DestroyTexture(namesTextTexture);
	SDL_DestroyTexture(scoresTextTexture);
}

endGameScreen::endGameScreen()
{

}


endGameScreen::~endGameScreen()
{
}
