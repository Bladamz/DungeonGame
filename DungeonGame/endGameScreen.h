#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class endGameScreen
{
public:
	endGameScreen();
	~endGameScreen();
	void getVictory(SDL_Renderer* renderer);
	void getDefeat(SDL_Renderer* renderer);
};

