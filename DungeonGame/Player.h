#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "Animation.h"

class Player : public Entity
{
private :
	float experience;			//players current experience
	int playerLevel;			//level of the player 1-100....
	float levelUpExperience;	//experience needed to level up
	bool levelUpRunning;
	Animation* animation = NULL;
	bool faceRight = true;
	int coins;
public:
	Player();
	//animatino related
	void setAnimation(Animation* animation);
	//overriding
	virtual void update(float dt);
	virtual void draw(float scale);


	void setExperience(float);
	float getExperience();
	float getLevelUpExperience();
	void addExperience(float);
	void calculateExperienceNeeded();
	void levelUp();

	float getStrength();
	float getDefence();
	float getCritChance();
	float getLevel();

	int getCoins();
	void addCoins(int);
	void setCoins(int);
};

