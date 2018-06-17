#include "Player.h"

Player::Player()
{
	objectName = "Knight";
	strength = 5;
	defence = 10;
	hP = 140;
	critChance = 0.1;
	experience = 0;
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

void Player::levelUp()
{
	levelUpRunning = true;
	//init ui here

	while (levelUpRunning)
	{
		//draw level up UI here

		//action listeners for all the buttons


	}
	//after player has chosen add 1 to player level
	playerLevel++;					//add to player level
	setExperience(0);				//set the experience back to 0
	calculateExperienceNeeded();	//calculate next experience goal
}

int Player::getStrength()
{
	return strengthChange;
}

int Player::getDefence()
{
	return defenceChange;
}

int Player::getCritChance()
{
	return critChange;
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