#include <iostream>
#include <string>

using namespace std;

class Entity
{
private:
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
};
