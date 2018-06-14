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
}

void Player::setExperience(float exp)
{
	experience = exp;
}

float Player::getExperience()
{
	return experience;
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
