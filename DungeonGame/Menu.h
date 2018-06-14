#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GameLoop.h"
#include "Animation.h"
#include "Highscores.h"

using namespace std;

class Menu
{
private:
	int coins;
	bool menuExit;


public:
	Menu();
	~Menu();

	void displayMenu(SDL_Renderer* renderer);
	void characterCreation(SDL_Renderer* renderer);
	void viewHighScores(SDL_Renderer* renderer);

};

