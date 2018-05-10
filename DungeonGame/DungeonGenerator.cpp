#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator()
{
	walks = 0;
	steps = 0;
	direction = 0;
	//root postion so once a walk is over it knows to return to the start position to start walking again
	rootRow = ROW / 2;
	rootColumn = COLUMN / 2;
	dungeonSize = 0;
	entrancePlaced = 0;
	entrancePlacer = 0;
	exitPlacer = 0;
	exitPlaced = 0;
	objectPlacer = 0;
}

void DungeonGenerator::fillDungeon(int(*a)[COLUMN])
{
	//fill arrays
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			a[i][j] = 0;
		}
	}
}

//print arrays
void DungeonGenerator::printDungeon(int(*a)[COLUMN])
{
	//print out data map
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (*(*(a + i) + j) > 0)
				cout << *(*(a + i) + j);
			else
				cout << " ";
		}
		cout << endl;
	}

	cout << "\n\n\n\n\n";

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (a[i][j] == 0)
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}

}

void DungeonGenerator::generateDungeon(int(*arr)[COLUMN], int diff)
{


	//place a 1 on any tile we walk on, indicating its not a wall for later use
	arr[ROW / 2][COLUMN / 2] = 1;

	//determines the size of the cave/dungeon based on the difficulty (which can be interpreted as floor level)
	dungeonSize = diff * 10;
	walks = dungeonSize;

	while (walks > 0)
	{
		currentColumn = rootColumn;
		currentRow = rootRow;

		steps = dungeonSize;

		while (steps > 0)
		{
			//choose direction
			direction = (rand() % 100) + 1;
			//north
			if (direction < 25)
			{
				if ((currentRow - 1) >= 1)
				{
					arr[currentRow - 1][currentColumn] = 1;
					currentRow--;
				}
				else
					steps--;
			}
			//east
			else if (direction < 50)
			{
				if ((currentColumn + 1) <= (COLUMN - 2))
				{
					arr[currentRow][currentColumn + 1] = 1;
					currentColumn++;
				}
				else
					steps--;
			}
			//south
			else if (direction < 75)
			{
				if ((currentRow + 1) <= (ROW - 2))
				{
					arr[currentRow + 1][currentColumn] = 1;
					currentRow++;
				}
				else
					steps--;
			}
			//west
			else
			{
				if ((currentColumn - 1) >= 1)
				{
					arr[currentRow][currentColumn - 1] = 1;
					currentColumn--;
				}
				else
					steps--;
			}
			steps--;
		}
		walks--;
	}
	placeEntrance(arr);
	placeExit(arr);
	spawnEvents(arr);
}

void DungeonGenerator::placeEntrance(int(*a)[COLUMN])
{
	//place entrance (NUMBER 8)
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (a[i][j] == 1)
			{
				while (entrancePlaced != 1)
				{
					entrancePlacer = rand() % COLUMN;
					if (a[i][entrancePlacer] == 1)
					{
						a[i][entrancePlacer] = 8;
						entrancePlaced = 1;
						i = ROW;
						j = COLUMN;
					}
				}
			}
		}
	}
}

void DungeonGenerator::placeExit(int(*a)[COLUMN])
{
	//place exit (NUMBER 9)
	for (int i = ROW - 1; i > 0; i--)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (a[i][j] == 1)
			{
				while (exitPlaced != 1)
				{
					exitPlacer = rand() % COLUMN;
					if (a[i][exitPlacer] == 1)
					{
						a[i][exitPlacer] = 9;
						exitPlaced = 1;
						i = ROW;
						j = COLUMN;
					}
				}
			}
		}
	}
}

void DungeonGenerator::spawnEvents(int(*a)[COLUMN])
{
	//Make Cave tiles random numbers which represent events
	//2 Is nothing
	//3 is enemy
	//4 is loot
	//5 is event
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (a[i][j] == 1)
			{
				objectPlacer = rand() % 100 + 1;
				if (objectPlacer < 40)
				{
					a[i][j] = 2;
				}
				else if (objectPlacer < 75)
				{
					a[i][j] = 3;
				}
				else if (objectPlacer < 85)
				{
					a[i][j] = 4;
				}
				else
				{
					a[i][j] = 5;
				}
			}
		}
	}
}