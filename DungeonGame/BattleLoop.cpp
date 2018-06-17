#include "BattleLoop.h"


BattleLoop::BattleLoop()
{
	reward = 0;
}

BattleLoop::~BattleLoop()
{
}

int BattleLoop::runBattleLoop(SDL_Renderer* renderer)
{
	Entity *player = NULL;
	player = new Player();
	Entity *enemy = NULL;
	enemy = new Zombie();




	//init art
	//load surfaces from assets folder
	SDL_Surface* uiBarSurface = IMG_Load("assets/battle/UiBar.png");
	SDL_Surface* attackButtonSurface = IMG_Load("assets/battle/AttackButton.png");
	SDL_Surface* defendButtonSurface = IMG_Load("assets/battle/DefendButton.png");
	SDL_Surface* focusButtonSurface = IMG_Load("assets/battle/FocusButton.png");
	SDL_Surface* runButtonSurface = IMG_Load("assets/battle/RunButton.png");
	SDL_Surface* backgroundSurface = IMG_Load("assets/menu/background.png");
	
	//convert surface to texture 
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_Texture* uiBarTexture = SDL_CreateTextureFromSurface(renderer, uiBarSurface);
	SDL_Texture* attackButtonTexture = SDL_CreateTextureFromSurface(renderer, attackButtonSurface);
	SDL_Texture* defendButtonTexture = SDL_CreateTextureFromSurface(renderer, defendButtonSurface);
	SDL_Texture* focusButtonTexture = SDL_CreateTextureFromSurface(renderer, focusButtonSurface);
	SDL_Texture* runButtonTexture = SDL_CreateTextureFromSurface(renderer, runButtonSurface);

	//delete surface properly
	SDL_FreeSurface(backgroundSurface);
	SDL_FreeSurface(uiBarSurface);
	SDL_FreeSurface(attackButtonSurface);
	SDL_FreeSurface(defendButtonSurface);
	SDL_FreeSurface(focusButtonSurface);
	SDL_FreeSurface(runButtonSurface);

	//destination of background
	SDL_Rect backgroundDesination;
	backgroundDesination.x = 0;
	backgroundDesination.y = -100;
	SDL_Rect uiBarDestination;
	uiBarDestination.x = 0;
	uiBarDestination.y = 550;
	SDL_Rect attackButtonDestination;
	attackButtonDestination.x = 0;
	attackButtonDestination.y = 550;
	SDL_Rect defendButtonDestination;
	defendButtonDestination.x = 227;
	defendButtonDestination.y = 550;
	SDL_Rect focusButtonDestination;
	focusButtonDestination.x = 0;
	focusButtonDestination.y = 635;
	SDL_Rect runButtonDestination;
	runButtonDestination.x = 227;
	runButtonDestination.y = 635;

	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundDesination.w, &backgroundDesination.h);
	SDL_QueryTexture(uiBarTexture, NULL, NULL, &uiBarDestination.w, &uiBarDestination.h);
	SDL_QueryTexture(attackButtonTexture, NULL, NULL, &attackButtonDestination.w, &attackButtonDestination.h);
	SDL_QueryTexture(defendButtonTexture, NULL, NULL, &defendButtonDestination.w, &defendButtonDestination.h);
	SDL_QueryTexture(focusButtonTexture, NULL, NULL, &focusButtonDestination.w, &focusButtonDestination.h);
	SDL_QueryTexture(runButtonTexture, NULL, NULL, &runButtonDestination.w, &runButtonDestination.h);

	

	//Animation Init
	SDL_Surface* knightSurface = IMG_Load("assets/menu/knight.png");
	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
	SDL_FreeSurface(knightSurface);

	Animation knight1(knightTexture, renderer, 45, 112, 151, 0.09);
	Animation knight2(knightTexture, renderer, 45, 112, 151, 0.05);

	//load art and other needed assets

	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	SDL_Event e;
		
	while (!player->checkIfDead() && !enemy->checkIfDead())
	{
		
		//difference is current time running minus the last update time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert into deltaTime (decimal)
		float DT = timeDiff / 1000.0; //e.g 200ms now = 0.2 for DT
									  //now update lastUpdate to the current time so the next loop calculates correctly
		lastUpdate = SDL_GetTicks();
		
		//draw background
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundDesination);

		//draw character HERO & ENEMY
		//update animations
		knight1.update(DT);
		knight2.update(DT);

		//draw from animations
		knight1.draw(150, 250, 2.0f);
		knight2.draw(900, 250, 2.0f);


		//draw UI
		SDL_RenderCopy(renderer, uiBarTexture, NULL, &uiBarDestination);
		SDL_RenderCopy(renderer, attackButtonTexture, NULL, &attackButtonDestination);
		SDL_RenderCopy(renderer, defendButtonTexture, NULL, &defendButtonDestination);
		SDL_RenderCopy(renderer, focusButtonTexture, NULL, &focusButtonDestination);
		SDL_RenderCopy(renderer, runButtonTexture, NULL, &runButtonDestination);

		displayHp(player, renderer);
		displayHp(enemy, renderer);
		
		

		//INPUT HANDLER		//input handler 
		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				battle = false;
				//SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked on the attack button
					if (e.button.x >= attackButtonDestination.x && e.button.x <= attackButtonDestination.x + 227 && e.button.y >= attackButtonDestination.y && e.button.y <= attackButtonDestination.y + 85)
					{
						enemy->takeDamage(player->turn());
						cout << "\n\n+---------------------------------------------------------------------------+\n\n";
						if (!enemy->checkIfDead())
						{
							player->takeDamage(enemy->turn());
							cout << "\n";
						}
					}
					//check if mouse is clicked on the defend button
					if (e.button.x >= defendButtonDestination.x && e.button.x <= defendButtonDestination.x + 227 && e.button.y >= defendButtonDestination.y && e.button.y <= defendButtonDestination.y + 85)
					{
						cout << "Player has increased their defence by 5." << endl;
						player->setDefenceChange(5);
						cout << "\n\n+---------------------------------------------------------------------------+\n\n";
						if (!enemy->checkIfDead())
						{
							player->takeDamage(enemy->turn());
							cout << "\n";
						}
					}
					//check if mouse is clicked on the focus button
					if (e.button.x >= focusButtonDestination.x && e.button.x <= focusButtonDestination.x + 227 && e.button.y >= focusButtonDestination.y && e.button.y <= focusButtonDestination.y + 85)
					{
						cout << "Player has increased their crit chance by 1%." << endl;
						player->setFocusChange(1);
						cout << "\n\n+---------------------------------------------------------------------------+\n\n";
						if (!enemy->checkIfDead())
						{
							player->takeDamage(enemy->turn());
							cout << "\n";
						}
					}
					//check if mouse is clicked on the run button
					if (e.button.x >= runButtonDestination.x && e.button.x <= runButtonDestination.x + 227 && e.button.y >= runButtonDestination.y && e.button.y <= runButtonDestination.y + 85)
					{
						enemy->setHpChange(5000000000); //kill enemy
					}

				}
			}
		}
		//if action happens do calculations
		//eg attack defend flee;
		//click buttons for menu and ui


		SDL_RenderPresent(renderer);
		
		//if player or enemy HP < 0 
		//battle = false;
	}

	return reward;
}

void BattleLoop::displayHp(Entity* entity, SDL_Renderer* renderer)
{
	string text = to_string(entity->getHpChange());

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);	//params: font file, font size
	SDL_Color textColor = { 0, 0, 0, 0 };

	// now create a surface from the font
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text_surface);

	//delete surface properly
	SDL_FreeSurface(text_surface);

	//text destination
	SDL_Rect textDestination;
	if (entity->getIsPlayer())
	{
		textDestination.x = 20;
		textDestination.y = 500;
	}
	else
	{
		textDestination.x = 1220;
		textDestination.y = 500;
	}
	

	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
}