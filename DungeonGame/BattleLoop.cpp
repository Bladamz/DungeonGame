#include "BattleLoop.h"


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

