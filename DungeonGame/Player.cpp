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

void Knight::setAnimation(Animation* animation) 
{

}

//overriding 
void Knight::update(float dt)
{
	//face direction based on velocity.x value
	if (velocity.x > 0) {
		faceRight = true;
	}
	if (velocity.x < 0) {
		faceRight = false;
	}

	//use basic entity movement to move around
	updateMovement(dt);

	//update animations too
	animation->update(dt);
}

void Knight::draw() {
	if (animation != NULL) {
		if (faceRight)
		{
			animation->draw(pos.x, pos.y);
		}
		else
		{
			animation->draw(pos.x, pos.y, true);
		}
	}
}