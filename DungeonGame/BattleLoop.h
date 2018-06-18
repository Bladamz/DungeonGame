#include <iostream>
#include <SDL.h>
#include <string>
#include <sstream>
#include <iomanip> // setprecision

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
	bool coward;
	Player* player;
	Enemy* enemy;
	TTF_Font* font;

public:
	BattleLoop();
	~BattleLoop();

	int runBattleLoop(SDL_Renderer* renderer, Player* knightPlayer, float floor);
	void displayHp(Entity* entity, SDL_Renderer* renderer);
	void diplayStats(Player* player, SDL_Renderer* renderer);
};

