#include "Enemy.h"

Enemy::Enemy(int enemyChoice)
{
	if (enemyChoice == 1)
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
	else if(enemyChoice == 2)
	{
		//construct skeleton
		objectName = "Skeleton";
		strength = 1;
		defence = 1;
		hP = 120;
		critChance = 0.4;

		defenceChange = defence;
		hPChange = hP;
		critChange = critChance;
		strengthChange = strength;
		isPlayer = false;
	}
}

float Enemy::moves()
{
	cout << "zombie attack" << endl;
	return 5;
}

