#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "Animation.h"

class Knight : public Entity
{
private:
	Animation* animation = NULL;
	bool faceRight = true;
public:
	Knight();

	float moves();

	void setAnimation(Animation* animation);

	//overriding
	virtual void update(float dt);
	virtual void draw();
	
};

