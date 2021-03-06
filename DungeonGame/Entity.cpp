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
void Entity::rest()
{
	hPChange = hP;
	defenceChange = defence;
	critChange = critChance;
	strengthChange = strength;
}

void Entity::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

float Entity::getPositionX()
{
	return pos.x;
}

float Entity::getPositionY()
{
	return pos.y;
}

void Entity::setPosition(Vector pos)
{
	this->pos = pos;
}

Vector Entity::getVelocity()
{
	return velocity;
}

void Entity::setVelocity(Vector velocity)
{
	this->velocity = velocity;
}

void Entity::update(float dt)
{
	updateMovement(dt);
}

void Entity::updateMovement(float dt)
{
	pos.x = pos.x + velocity.x*dt;
	pos.y = pos.y + velocity.y*dt;
}

void Entity::draw(float scale)
{
	//do nothing, let others override this
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
		if (critChange >= critRoll)
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
	float damageTaken = (damage - (damage*(defenceChange / 50)));
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

void Entity::setDefenceChange(float change)
{
	defenceChange = defenceChange + change;
}

void Entity::setCritChange(float change)
{
	critChange = critChange + change;
}

void Entity::setHpChange(float change)
{
	hPChange = hPChange - change;
}

float Entity::getHpChange()
{
	return hPChange;
}

bool Entity::getIsPlayer()
{
	return isPlayer;
}