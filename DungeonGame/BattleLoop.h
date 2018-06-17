#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"


using namespace std;

class BattleLoop
{
private:
	int reward;
	bool battle;
	Player* player;
	Enemy* enemy;

public:
	BattleLoop();
	~BattleLoop();

	int runBattleLoop(SDL_Renderer* renderer, Player* knightPlayer);
	void displayHp(Entity* entity, SDL_Renderer* renderer);
	void diplayStats(Player* player, SDL_Renderer* renderer);
};

