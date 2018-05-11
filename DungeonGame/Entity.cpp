#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::displayStats() 
{
	//Bring up scren showing player stats
	cout << "STATS OF PLAYER" << endl;
}

string Entity::getSubName()
{
	return objectName;
}

bool Entity::playerCheck()
{
	return isPlayer;
}

//Post battle fucntions
void Entity::levelUp()
{
	//ASK PLAYER TO LEVEL UP A STAT
	cout << "LEVEL UP" << endl;

}

void Entity::rest()
{
	hPChange = hP;
	defenceChange = defence;
	critChange = critChance;
	strengthChange = strength;
}


//combat functions
float Entity::turn()
{
	//choose abilities
	float damage = 0;
	damage = this->moves() * ((strength / 100) + 1);

	if (damage > 0)
	{
		//roll crit 
		float critRoll = rand() % 100;
		critRoll = critRoll / 100;
		//test to see if crit is sucessful
		if (critChance >= critRoll)
		{

			cout << "\t" << objectName << " have dealt a critical hit!" << endl;
			damage = damage * 2; //x2 damage
		}
	}
	return damage;
}

void Entity::takeDamage(float damage)
{
	//midigate damage with defence
	float damageTaken = (damage - (damage*(defence / 100)));
	if (damageTaken > 0)
	{
		//take HP damage
		hPChange = hPChange - damageTaken;
		if (objectName == "Knight" || objectName == "Rogue" || objectName == "Wizard")
		{
			cout << "\tYou have taken " << damageTaken << " HP damage!" << endl;
			cout << "\tPlayer HP is now " << hPChange << endl;
		}
		else
		{
			cout << "\tThe enemy " << objectName << " has taken " << damageTaken << " HP damage!" << endl;
			cout << "\t" << objectName << " HP is now " << hPChange << endl;
		}
	}
}

float Entity::moves()
{
	cout << "Do some attack!" << endl;
	return 10;
}

bool Entity::checkIfDead()
{
	return (hPChange < 1);
}