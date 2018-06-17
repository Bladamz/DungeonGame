#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <vector>

using namespace std;

class Highscores
{
public:
	Highscores();
	~Highscores();
	string getHighscore();
	void checkNewScore(string name, int newScore);
	void update();

private:
	string checkLine;
	string checkWord[30];
	string outputLine[10];
	string highscoreNameArr[10];
	string display;
	int highscoreScoreArr[10];
	int highscoreNumberArr[10];
	void testFile();
};

