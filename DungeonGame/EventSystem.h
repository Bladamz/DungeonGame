#pragma once

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Player.h"
#include "BattleLoop.h"

using namespace std;

class EventSystem
{
private:
	BattleLoop* battleLoop;
	float eventExperience;
	float eventCoins;
	bool eventRunning;
	string eventMessage;
	TTF_Font* font;
	Mix_Music* battleMusic;
public:
	EventSystem();
	~EventSystem();
	float experienceEvent(SDL_Renderer* renderer);
	float coinEvent(SDL_Renderer* renderer);
	void checkEvent(int, int, int(*a)[40], SDL_Renderer*,Player* player, float, Mix_Music*);
};

