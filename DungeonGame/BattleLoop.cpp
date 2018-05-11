#include "BattleLoop.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

BattleLoop::BattleLoop()
{
	reward = 0;
	battle = true;
}

BattleLoop::~BattleLoop()
{
}

int BattleLoop::runBattleLoop(SDL_Renderer* renderer)
{
	Entity *player = NULL;
	player = new Knight();
	Entity *enemy = NULL;
	enemy = new Zombie();

	//combat module
	while (!player->checkIfDead() && !enemy->checkIfDead())
	{
		enemy->takeDamage(player->turn());
		cout << "\n\n+---------------------------------------------------------------------------+\n\n";
		if (!enemy->checkIfDead())
		{
			player->takeDamage(enemy->turn());
			cout << "\n";
		}
	}
	//init art

	//load art and other needed assets
		
	while (battle)
	{
		//draw background
		
		//draw character HERO & ENEMY

		//draw UI

		//INPUT HANDLER
		//if action happens do calculations
		//eg attack defend flee;
		//click buttons for menu and ui


		//SDL_RenderPresent(renderer);
		
		//if player or enemy HP < 0 
		battle = false;
	}

	return reward;
}

