#pragma once
#include <list>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "DungeonGenerator.h"
#include "Animation.h"
#include "Player.h"
#include "EventSystem.h"
#include "Timer.h"
#include "endGameScreen.h"

class GameLoop
{
public:
	SDL_Texture * knightTexture;
	Animation* knightAnimation;
	Player* knight;
	EventSystem* eventSystem;
	bool gameRunning;
	bool floorRunning;
	int dungeon;
	int floor;
	int spawnPosX;
	int spawnPosY;
	int arrayPosX;
	int arrayPosY;
	int playerOffSetX;
	int playerOffSetY;

	list<Entity*> entities;

	//TIME STUFF
	Uint32 lastUpdate; //last sdl_ticks
	float dt = 0; //time since last update

	GameLoop(SDL_Renderer* renderer);
	~GameLoop();

	int runGameLoop(SDL_Renderer* renderer);

};

