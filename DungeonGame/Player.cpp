
#include "Player.h"

Knight::Knight()
{
	objectName = "Knight";
	strength = 5;
	defence = 10;
	hP = 140;
	critChance = 0.1;

	defenceChange = defence;
	hPChange = hP;
	critChange = critChance;
	strengthChange = strength;
	isPlayer = true;
}

float Knight::moves()
{
	return 10;
}