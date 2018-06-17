#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"


using namespace std;

class BattleLoop
{
private:
	int reward;
	bool battle;

public:
	BattleLoop();
	~BattleLoop();

	int runBattleLoop(SDL_Renderer* renderer);
	void displayHp(Entity* entity, SDL_Renderer* renderer);
};

