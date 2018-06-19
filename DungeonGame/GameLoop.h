#pragma once
#include <list>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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
	float floor;
	int spawnPosX;
	int spawnPosY;
	int arrayPosX;
	int arrayPosY;
	int playerOffSetX;
	int playerOffSetY;
	TTF_Font* font;

	list<Entity*> entities;

	Mix_Music* dungeonMusic;

	//TIME STUFF
	Uint32 lastUpdate; //last sdl_ticks
	float dt = 0; //time since last update

	//Displaying UI
	void displayUI(SDL_Renderer* renderer, Player* player, float);
	void displayMap(SDL_Renderer* renderer, int(*dungeon)[40]);
	GameLoop(SDL_Renderer* renderer);
	~GameLoop();

	int runGameLoop(SDL_Renderer* renderer);

};

