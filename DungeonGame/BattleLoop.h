#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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
};

