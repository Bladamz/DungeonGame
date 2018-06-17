#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public: 
	float moves();
	Enemy(int);
};
