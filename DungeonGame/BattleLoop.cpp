#include "BattleLoop.h"


BattleLoop::BattleLoop()
{
	reward = 0;
	coward = false;
	srand(time(NULL));
	font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);	
}

BattleLoop::~BattleLoop()
{
	font = NULL;
	delete font;
}

int BattleLoop::runBattleLoop(SDL_Renderer* renderer, Player* knightPlayer, float floor)
{
	player = knightPlayer;
	enemy = new Enemy((rand() % 2 + 1),floor);
	Timer timer;

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
	SDL_Surface* knightSurface = IMG_Load("assets/battle/CharacterIdle.png");
	SDL_Surface* enemySurface = IMG_Load("assets/menu/knight.png");
	SDL_Surface* knightSwingSurface = IMG_Load("assets/battle/CharacterSwing.png");

	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
	SDL_Texture* enemyTexture = SDL_CreateTextureFromSurface(renderer, enemySurface);
	SDL_Texture* knightSwingTexture = SDL_CreateTextureFromSurface(renderer, knightSwingSurface);

	SDL_FreeSurface(knightSurface);
	SDL_FreeSurface(enemySurface);
	SDL_FreeSurface(knightSwingSurface);

	//some shit animation code because I ran out of time
	SDL_Surface* zombieSurface = IMG_Load("assets/battle/ZombieIdle.png");
	SDL_Surface* zombieSwingSurface = IMG_Load("assets/battle/ZombieSwing.png");

	SDL_Texture* zombieTexture = SDL_CreateTextureFromSurface(renderer, zombieSurface);
	SDL_Texture* zombieSwingTexture = SDL_CreateTextureFromSurface(renderer, zombieSwingSurface);

	SDL_FreeSurface(zombieSurface);
	SDL_FreeSurface(zombieSwingSurface);

	Animation zombieIdle(zombieTexture, renderer, 15, 476, 381, 0.06);
	Animation zombieSwing(zombieSwingTexture, renderer, 15, 476, 381, 0.02);
		
	SDL_Surface* skeletonSurface = IMG_Load("assets/battle/SkeletonIdle.png");
	SDL_Surface* skeletonSwingSurface = IMG_Load("assets/battle/SkeletonSwing.png");

	SDL_Texture* skeletonTexture = SDL_CreateTextureFromSurface(renderer, skeletonSurface);
	SDL_Texture* skeletonSwingTexture = SDL_CreateTextureFromSurface(renderer, skeletonSwingSurface);

	SDL_FreeSurface(skeletonSurface);
	SDL_FreeSurface(skeletonSwingSurface);

	Animation skeletonIdle(skeletonTexture, renderer, 15, 476, 381, 0.06);
	Animation skeletonSwing(skeletonSwingTexture, renderer, 15, 476, 381, 0.02);

	Animation knight(knightTexture, renderer, 15, 179, 179, 0.1);
	Animation knightSwing(knightSwingTexture, renderer, 15, 179, 178, 0.02);

	//load art and other needed assets

	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	SDL_Event e;

	bool playerAttacking = false;
	bool enemyAttacking = false;
		
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

		//draw from animations
		knightSwing.update(DT);
		knight.update(DT);

		if (playerAttacking)
		{
			//knightSwing.update(DT);
			knightSwing.draw(300, 200, 2.0f);
		}
		else
		{
			//knight.update(DT);
			knight.draw(300, 200, 2.0f);
		}

		//terrible code for managing aimations
		if (enemyAttacking)
		{
			if (enemy->getSubName() == "Zombie")
			{
				zombieSwing.update(DT);
				zombieSwing.draw(700, 200, 1.0f);
			}
			else
			{
				skeletonSwing.update(DT);
				skeletonSwing.draw(700, 200, 1.0f, true);
			}
		}
		else
		{
			if (enemy->getSubName() == "Zombie")
			{
				zombieIdle.update(DT);
				zombieIdle.draw(700, 200, 1.0f);
			}
			else
			{
				skeletonIdle.update(DT);
				skeletonIdle.draw(700, 200, 1.0f, true);
			}
		}

		//draw UI buttons
		SDL_RenderCopy(renderer, uiBarTexture, NULL, &uiBarDestination);
		SDL_RenderCopy(renderer, attackButtonTexture, NULL, &attackButtonDestination);
		SDL_RenderCopy(renderer, defendButtonTexture, NULL, &defendButtonDestination);
		SDL_RenderCopy(renderer, focusButtonTexture, NULL, &focusButtonDestination);
		SDL_RenderCopy(renderer, runButtonTexture, NULL, &runButtonDestination);


		//draw HP and UI
		displayHp(player, renderer);
		displayHp(enemy, renderer);
		diplayStats(player, renderer);
		if (timer.isStarted() && (timer.getTicks() >= 400))
		{
			enemyAttacking = true;
			playerAttacking = false;
		}


		if (timer.isStarted() && (timer.getTicks() >= 1000))
		{
			timer.stop();
			playerAttacking = false;
			enemyAttacking = false;
		}

		//INPUT HANDLER		//input handler 
		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit game
				battle = false;
				SDL_Quit();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN && !timer.isStarted())
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked on the attack button
					if (e.button.x >= attackButtonDestination.x && e.button.x <= attackButtonDestination.x + 227 && e.button.y >= attackButtonDestination.y && e.button.y <= attackButtonDestination.y + 85)
					{
						playerAttacking = true;
						enemy->takeDamage(player->turn());
						timer.start();
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
							timer.start();
							player->takeDamage(enemy->turn());
							cout << "\n";
							enemyAttacking = true;
						}
					}
					//check if mouse is clicked on the focus button
					if (e.button.x >= focusButtonDestination.x && e.button.x <= focusButtonDestination.x + 227 && e.button.y >= focusButtonDestination.y && e.button.y <= focusButtonDestination.y + 85)
					{
						timer.start();
						cout << "Player has increased their crit chance by 1%." << endl;
						player->setFocusChange(1);
						cout << "\n\n+---------------------------------------------------------------------------+\n\n";
						if (!enemy->checkIfDead())
						{
							player->takeDamage(enemy->turn());
							cout << "\n";
							enemyAttacking = true;
						}
					}
					//check if mouse is clicked on the run button
					if (e.button.x >= runButtonDestination.x && e.button.x <= runButtonDestination.x + 227 && e.button.y >= runButtonDestination.y && e.button.y <= runButtonDestination.y + 85)
					{
						enemy->setHpChange(5000000000); //kill enemy
						cout << "Coward" << endl;
						battle = false;
						coward = true;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}

	//calculate coins based on outcome of battle
	if (enemy->checkIfDead() == true && !coward)
	{
		reward = rand() % 300 + 100;
	}
	else
	{
		reward = 0;
	}

	SDL_DestroyTexture(uiBarTexture);
	SDL_DestroyTexture(attackButtonTexture);
	SDL_DestroyTexture(defendButtonTexture);
	SDL_DestroyTexture(focusButtonTexture);
	SDL_DestroyTexture(runButtonTexture);
	SDL_DestroyTexture(backgroundTexture);

	return reward;
}

void BattleLoop::diplayStats(Player* player, SDL_Renderer* renderer)
{
	stringstream stream;
	string s;
	
	string strength = "Strength: ";
	stream << fixed << setprecision(0) << player->getStrength();
	s = stream.str();
	strength += s;

	stream.str(string());
	stream.clear();

	string defence = "Defence: ";
	stream << fixed << setprecision(0) << player->getDefence();
	s = stream.str();
	defence += s;

	stream.str(string());
	stream.clear();

	string critChance = "Crit Chacnce: ";
	stream << fixed << setprecision(2) << player->getCritChance();
	s = stream.str();
	critChance += s;

	stream.str(string());
	stream.clear();

	string experience = "Experience: ";
	stream << fixed << setprecision(0) << player->getExperience();
	s = stream.str();
	experience += s;

	
	SDL_Color textColor = { 0, 0, 0, 0 };
	if (font)
	{
		// now create a surface from the font
		SDL_Surface* strengthSurface = TTF_RenderText_Solid(font, strength.c_str(), textColor);
		SDL_Surface* defenceSurface = TTF_RenderText_Solid(font, defence.c_str(), textColor);
		SDL_Surface* critSurface = TTF_RenderText_Solid(font, critChance.c_str(), textColor);
		SDL_Surface* expSurface = TTF_RenderText_Solid(font, experience.c_str(), textColor);

		//convert surface to texture
		SDL_Texture* strengthTextTexture = SDL_CreateTextureFromSurface(renderer, strengthSurface);
		SDL_Texture* defenceTextTexture = SDL_CreateTextureFromSurface(renderer, defenceSurface);
		SDL_Texture* critTextTexture = SDL_CreateTextureFromSurface(renderer, critSurface);
		SDL_Texture* expTextTexture = SDL_CreateTextureFromSurface(renderer, expSurface);

		//delete surface properly
		SDL_FreeSurface(strengthSurface);
		SDL_FreeSurface(defenceSurface);
		SDL_FreeSurface(critSurface);
		SDL_FreeSurface(expSurface);

		//text destination
		SDL_Rect strengthDestination;
		strengthDestination.x = 600;
		strengthDestination.y = 560;

		SDL_Rect defenceDestination;
		defenceDestination.x = 900;
		defenceDestination.y = 560;

		SDL_Rect critDestination;
		critDestination.x = 600;
		critDestination.y = 660;

		SDL_Rect expDestination;
		expDestination.x = 900;
		expDestination.y = 660;

		SDL_QueryTexture(strengthTextTexture, NULL, NULL, &strengthDestination.w, &strengthDestination.h);
		SDL_QueryTexture(defenceTextTexture, NULL, NULL, &defenceDestination.w, &defenceDestination.h);
		SDL_QueryTexture(critTextTexture, NULL, NULL, &critDestination.w, &critDestination.h);
		SDL_QueryTexture(expTextTexture, NULL, NULL, &expDestination.w, &expDestination.h);

		SDL_RenderCopy(renderer, strengthTextTexture, NULL, &strengthDestination);
		SDL_RenderCopy(renderer, defenceTextTexture, NULL, &defenceDestination);
		SDL_RenderCopy(renderer, critTextTexture, NULL, &critDestination);
		SDL_RenderCopy(renderer, expTextTexture, NULL, &expDestination);

		SDL_DestroyTexture(strengthTextTexture);
		SDL_DestroyTexture(defenceTextTexture);
		SDL_DestroyTexture(critTextTexture);
		SDL_DestroyTexture(expTextTexture);
	}
}

void BattleLoop::displayHp(Entity* entity, SDL_Renderer* renderer)
{
	stringstream stream;
	string s;

	stream << fixed << setprecision(0) << entity->getHpChange();
	string text = stream.str();


	stream.str(string());
	stream.clear();

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

	SDL_DestroyTexture(textTexture);
}