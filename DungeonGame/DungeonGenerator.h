#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#define ROW 40
#define COLUMN 40

using namespace std;

class DungeonGenerator
{
private:
	int objectPlacer;
	int exitPlacer;
	int exitPlaced;
	int entrancePlacer;
	int entrancePlaced;
	int currentRow;
	int currentColumn;
	int walks;
	int steps;
	int direction;
	int rootRow;
	int rootColumn;
	int dungeonSize;
public:
	void fillDungeon(int(*a)[COLUMN]);
	void printDungeon(int(*a)[COLUMN]);
	void generateDungeon(int(*a)[COLUMN], int diff);
	void placeEntrance(int(*a)[COLUMN]);
	void placeExit(int(*a)[COLUMN]);
	void spawnEvents(int(*a)[COLUMN]);

	//constructor
	DungeonGenerator();
};