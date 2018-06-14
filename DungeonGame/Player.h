#pragma once

#include <iostream>
#include <string>

#include "Entity.h"

class Player : public Entity
{
private :
	float experience;			//players current experience
	int playerLevel;			//level of the player 1-100....
	float levelUpExperience;	//experience needed to level up
	bool levelUpRunning;
public:
	Player();
	void setExperience(float);
	float getExperience();
	void addExperience(float);
	void calculateExperienceNeeded();
	void levelUp();
};

