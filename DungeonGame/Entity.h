#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include "Vector.h"

using namespace std;

class Entity
{
protected:
	SDL_Renderer * renderer;
	//names for objects
	string playerName;	//used for the player name and later on in high score
	string objectName;	//used to label the Hero "Knight" or enemt "Zombie"

	//stats that will not change during battle
	float hP;	//health points of an entity
	float defence;	//how resistant to damage an entity is 
	float strength;	//how much damage will the entity do
	float critChance; //what % chance to crit does the entity have
	bool isPlayer;	//checking if entity is player or enemy

	//stats that change during battle
	float hPChange;	
	float defenceChange;
	float critChange;
	float strengthChange;

public:
	Entity();
	~Entity();

	//Vector related (positioning of entity)
	Vector pos; //entities xy position
	Vector velocity; //how fast to move within a direction

	void setRenderer(SDL_Renderer* renderer);
	float getPositionX();
	float getPositionY();
	void setPosition(Vector pos);
	Vector getVelocity();
	void setVelocity(Vector velocity);

	virtual void update(float dt);
	virtual void updateMovement(float dt);
	virtual void draw(float scale);

	//misc functions
	void displayStats();
	string getName(); //Player name for character
	string getSubName(); //name for enemies and hero roles eg kight, rogue, goblin
	bool playerCheck();

	float experience;			//players current experience
	int playerLevel;			//level of the player 1-100....
	float levelUpExperience;	//experience needed to level up
	bool levelUpRunning;

   //Post battle fucntions
	void rest();

	//combat functions
	float turn();
	void takeDamage(float);
	virtual float moves();
	bool checkIfDead();
	void setDefenceChange(int);
	void setFocusChange(int);
	void setHpChange(int);
	void setExperience(float);
	float getExperience();
	void addExperience(float);
	void calculateExperienceNeeded();
	void levelUp();
	int getHpChange();
	bool getIsPlayer();
};

