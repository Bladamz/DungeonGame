#include "Enemy.h"

Enemy::Enemy(int enemyChoice, float floor)
{
	if (enemyChoice == 1)
	{
		//construct zombie
		objectName = "Zombie";
		strength = 3 * (1 + (floor / 4));
		defence = 0.1 * (1 + (floor / 4));
		hP = 120 * (1 + (floor / 4));
		critChance = 0.1;

		defenceChange = defence;
		hPChange = hP;
		critChange = critChance;
		strengthChange = strength;
		isPlayer = false;
	}
	else if(enemyChoice == 2)
	{
		//construct skeleton
		objectName = "Skeleton";
		strength = 4 * (1 + (floor / 4));
		defence = 1 * (1 + (floor / 4));
		hP = 100 * (1 + (floor / 4));
		critChance = 0.4;

		defenceChange = defence;
		hPChange = hP;
		critChange = critChance;
		strengthChange = strength;
		isPlayer = false;
	}
}
