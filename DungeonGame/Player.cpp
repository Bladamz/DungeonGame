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

