#include "Enemy.h"

Zombie::Zombie()
{
	//construct zombie
	objectName = "Zombie";
	strength = 2;
	defence = 0;
	hP = 150;
	critChance = 0.1;

	defenceChange = defence;
	hPChange = hP;
	critChange = critChance;
	strengthChange = strength;
	isPlayer = false;
}

float Zombie::moves()
{
	cout << "zombie attack" << endl;
	return 5;
}
