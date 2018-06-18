#include "Player.h"

Player::Player()
{
	objectName = "Knight";
	strength = 5;
	defence = 10;
	hP = 140;
	critChance = 0.1;
	experience = 1000;
	playerLevel = 1;
	levelUpRunning = false;

	defenceChange = defence;
	hPChange = hP;
	critChange = critChance;
	strengthChange = strength;
	isPlayer = true;

	coins = 0;
}

void Player::setAnimation(Animation* animation)
{
	this->animation = animation;
}

//overriding
void Player::update(float dt)
{
	//face direction based on velocity.x value
	if (velocity.x > 0)
	{
		faceRight = true;
	}
	if (velocity.x < 0)
	{
		faceRight = false;
	}

	//use basic entity movement to move around
	updateMovement(dt);

	//update animations too
	animation->update(dt);
}

void Player::draw(float scale)
{
	if (animation != NULL)
	{
		if (faceRight)
		{
			animation->draw(pos.x, pos.y, scale);
		}
		else
		{
			animation->draw(pos.x, pos.y, scale, true);
		}
	}
}

void Player::setExperience(float exp)
{
	experience = exp;
}

float Player::getExperience()
{
	return experience;
}

float Player::getLevelUpExperience()
{
	return levelUpExperience;
}

void Player::addExperience(float exp)
{
	experience = experience + exp;
}

void Player::calculateExperienceNeeded()
{
	levelUpExperience = 1000 * ((playerLevel / 4) +1);
}

void Player::levelUp(SDL_Renderer* renderer)
{
	levelUpRunning = true;

	SDL_Surface* plusSurface = IMG_Load("assets/battle/plus2.png");

	//convert surface to texture 
	SDL_Texture* plusTexture1 = SDL_CreateTextureFromSurface(renderer, plusSurface);
	SDL_Texture* plusTexture2 = SDL_CreateTextureFromSurface(renderer, plusSurface);
	SDL_Texture* plusTexture3 = SDL_CreateTextureFromSurface(renderer, plusSurface);
	SDL_Texture* plusTexture4 = SDL_CreateTextureFromSurface(renderer, plusSurface);

	//delete surface properly
	SDL_FreeSurface(plusSurface);

	//destination of background
	SDL_Rect plus1Dest;
	plus1Dest.x = 500;
	plus1Dest.y = 90;

	SDL_Rect plus2Dest;
	plus2Dest.x = 500;
	plus2Dest.y = 170;

	SDL_Rect plus3Dest;
	plus3Dest.x = 500;
	plus3Dest.y = 260;

	SDL_Rect plus4Dest;
	plus4Dest.x = 500;
	plus4Dest.y = 340;

	SDL_QueryTexture(plusTexture1, NULL, NULL, &plus1Dest.w, &plus1Dest.h);
	SDL_QueryTexture(plusTexture2, NULL, NULL, &plus2Dest.w, &plus2Dest.h);
	SDL_QueryTexture(plusTexture3, NULL, NULL, &plus3Dest.w, &plus3Dest.h);
	SDL_QueryTexture(plusTexture4, NULL, NULL, &plus4Dest.w, &plus4Dest.h);

	string  levelUpText= "Strength +1\n\nDefence + 1\n\nCrit Chance + 0.1\n\nHp + 10";

	TTF_Font* font = TTF_OpenFont("assets/menu/BLKCHCRY.ttf", 32);
	SDL_Color textColor = { 255, 255, 255, 0 };

	//create a surface using this fonr to display some sort of message
	SDL_Surface* levelUpSurface = TTF_RenderText_Blended_Wrapped(font, levelUpText.c_str(), textColor, 1000);

	//convert surface to texture
	SDL_Texture* levelUpTextTexture = SDL_CreateTextureFromSurface(renderer, levelUpSurface);

	//delete surface properly
	SDL_FreeSurface(levelUpSurface);

	//text destination
	SDL_Rect levelUpDestination;
	levelUpDestination.x = 200;
	levelUpDestination.y = 100;

	//get width and height from texture and set it for the destination
	SDL_QueryTexture(levelUpTextTexture, NULL, NULL, &levelUpDestination.w, &levelUpDestination.h);

	SDL_Event e;

	while (levelUpRunning)
	{
		//set colour to black with some transparance
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
		//make a SDL_Rect, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 50, 50, 1180, 420 };
		//render rectangle to screen (renderer and a rectangle for positioning)
		SDL_RenderFillRect(renderer, &rect);

		//place text
		SDL_RenderCopy(renderer, levelUpTextTexture, NULL, &levelUpDestination);
		SDL_RenderCopy(renderer, plusTexture1, NULL, &plus1Dest);
		SDL_RenderCopy(renderer, plusTexture2, NULL, &plus2Dest);
		SDL_RenderCopy(renderer, plusTexture3, NULL, &plus3Dest);
		SDL_RenderCopy(renderer, plusTexture4, NULL, &plus4Dest);

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//check if its the left mouse button down
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//check if mouse is clicked on the attack button
					if (e.button.x >= plus1Dest.x && e.button.x <= plus1Dest.x + 227 && e.button.y >= plus1Dest.y && e.button.y <= plus1Dest.y + 85)
					{
						strength = strength + 1;
						levelUpRunning = false;
					}
					//check if mouse is clicked on the defend button
					if (e.button.x >= plus2Dest.x && e.button.x <= plus2Dest.x + 227 && e.button.y >= plus2Dest.y && e.button.y <= plus2Dest.y + 85)
					{
						defence = defence + 1;
						levelUpRunning = false;
					}
					//check if mouse is clicked on the focus button
					if (e.button.x >= plus3Dest.x && e.button.x <= plus3Dest.x + 227 && e.button.y >= plus3Dest.y && e.button.y <= plus3Dest.y + 85)
					{
						critChance = critChance + 0.1;
						levelUpRunning = false;
					}
					//check if mouse is clicked on the run button
					if (e.button.x >= plus4Dest.x && e.button.x <= plus4Dest.x + 227 && e.button.y >= plus4Dest.y && e.button.y <= plus4Dest.y + 85)
					{
						hP = hP + 10;
						levelUpRunning = false;
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
	//after player has chosen add 1 to player level
	playerLevel++;					//add to player level	
	rest();
	setExperience(0);				//set the experience back to 0
	calculateExperienceNeeded();	//calculate next experience goal
}

float Player::getStrength()
{
	return strengthChange;
}

float Player::getDefence()
{
	return defenceChange;
}

float Player::getCritChance()
{
	return critChange;
}

float Player::getLevel()
{
	return playerLevel;
}

int Player::getCoins()
{
	return coins;
}

void Player::addCoins(int addedCoins)
{
	coins = coins + addedCoins;
}	

void Player::setCoins(int setCoins)
{
	coins = setCoins;
}