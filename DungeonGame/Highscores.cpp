
#include "Highscores.h"

using namespace std;

// DON'T BOTHER READING MY CODE. IT'S MESSY AS FUCK! NO TIME TO CLEAN IT.
// checkNewScore("Dan", 3000);		Checks highscore against the text file and auto does everything for u. U send name and then score.
// getHighscore();					Returns Displayable text
// update();						Updates The Displayable Text


void Highscores::testFile() {
	ifstream highscoreFile("assets/Highscores.txt");
	if (!highscoreFile)
	{
		cout << "Error finding or using Highscores.txt file." << endl;
		cout << "Making new Highscores.txt file" << endl;
		ofstream file("assets/Highscores.txt");
		file.close();
	}
	else if (highscoreFile)
	{
		cout << "Highscores.txt Loaded :-D" << endl;
	}

	while (highscoreFile.good())
	{
		for (int i = 0; i < 30; i++)
		{
			getline(highscoreFile, checkLine, ' ');
			if (checkLine != "")
			{
				checkWord[i] = checkLine;
				checkLine = "";
			}
		}
	}
	highscoreFile.close();

	int allHighScoreCounter = 0;
	for (int l = 0; l < 10; l++)
	{
		highscoreNumberArr[l];
		allHighScoreCounter++;
		highscoreNameArr[l] = checkWord[allHighScoreCounter];
		allHighScoreCounter++;
		highscoreScoreArr[l] = stoi(checkWord[allHighScoreCounter]);
		allHighScoreCounter++;
	}
}

string Highscores::getHighscore() {
	return display;
}

void Highscores::checkNewScore(string name, int newScore) {
	for (int i = 0; i < 10; i++)
	{
		if (newScore > highscoreScoreArr[i])
		{
			if (i == 0)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = highscoreNameArr[4];
				highscoreScoreArr[5] = highscoreScoreArr[4];

				highscoreNameArr[4] = highscoreNameArr[3];
				highscoreScoreArr[4] = highscoreScoreArr[3];

				highscoreNameArr[3] = highscoreNameArr[2];
				highscoreScoreArr[3] = highscoreScoreArr[2];

				highscoreNameArr[2] = highscoreNameArr[1];
				highscoreScoreArr[2] = highscoreScoreArr[1];

				highscoreNameArr[1] = highscoreNameArr[0];
				highscoreScoreArr[1] = highscoreScoreArr[0];

				highscoreNameArr[0] = name;
				highscoreScoreArr[0] = newScore;
				i = 10;
			}
			else if (i == 1)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = highscoreNameArr[4];
				highscoreScoreArr[5] = highscoreScoreArr[4];

				highscoreNameArr[4] = highscoreNameArr[3];
				highscoreScoreArr[4] = highscoreScoreArr[3];

				highscoreNameArr[3] = highscoreNameArr[2];
				highscoreScoreArr[3] = highscoreScoreArr[2];

				highscoreNameArr[2] = highscoreNameArr[1];
				highscoreScoreArr[2] = highscoreScoreArr[1];

				highscoreNameArr[1] = name;
				highscoreScoreArr[1] = newScore;
				i = 10;
			}
			else if (i == 2)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = highscoreNameArr[4];
				highscoreScoreArr[5] = highscoreScoreArr[4];

				highscoreNameArr[4] = highscoreNameArr[3];
				highscoreScoreArr[4] = highscoreScoreArr[3];

				highscoreNameArr[3] = highscoreNameArr[2];
				highscoreScoreArr[3] = highscoreScoreArr[2];

				highscoreNameArr[2] = name;
				highscoreScoreArr[2] = newScore;
				i = 10;
			}
			else if (i == 3)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = highscoreNameArr[4];
				highscoreScoreArr[5] = highscoreScoreArr[4];

				highscoreNameArr[4] = highscoreNameArr[3];
				highscoreScoreArr[4] = highscoreScoreArr[3];

				highscoreNameArr[3] = name;
				highscoreScoreArr[3] = newScore;
				i = 10;
			}
			else if (i == 4)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = highscoreNameArr[4];
				highscoreScoreArr[5] = highscoreScoreArr[4];

				highscoreNameArr[4] = name;
				highscoreScoreArr[4] = newScore;
				i = 10;
			}
			else if (i == 5)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = highscoreNameArr[5];
				highscoreScoreArr[6] = highscoreScoreArr[5];

				highscoreNameArr[5] = name;
				highscoreScoreArr[5] = newScore;
				i = 10;
			}
			else if (i == 6)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = highscoreNameArr[6];
				highscoreScoreArr[7] = highscoreScoreArr[6];

				highscoreNameArr[6] = name;
				highscoreScoreArr[6] = newScore;
				i = 10;
			}
			else if (i == 7)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = highscoreNameArr[7];
				highscoreScoreArr[8] = highscoreScoreArr[7];

				highscoreNameArr[7] = name;
				highscoreScoreArr[7] = newScore;
				i = 10;
			}
			else if (i == 8)
			{
				highscoreNameArr[9] = highscoreNameArr[8];
				highscoreScoreArr[9] = highscoreScoreArr[8];

				highscoreNameArr[8] = name;
				highscoreScoreArr[8] = newScore;
				i = 10;
			}
			else if (i == 9)
			{
				highscoreNameArr[9] = name;
				highscoreScoreArr[9] = newScore;
				i = 10;
			}
			ofstream highscoreTxt;
			highscoreTxt.open("assets/highscores.txt");
			string textFile = "";
			display = "";
			int allHighScoreCounter = 0;
			for (int k = 0; k < 10; k++)
			{
				textFile += to_string(highscoreNumberArr[k]) + " " + highscoreNameArr[k] + " " + to_string(highscoreScoreArr[k]) + " ";
				display += to_string(highscoreNumberArr[k]) + " " + highscoreNameArr[k] + " " + to_string(highscoreScoreArr[k]) + "\n";
				allHighScoreCounter+= 3;
			}
			highscoreTxt << textFile;
			textFile = "";
			highscoreTxt.close();
		}
	}
	
}

void Highscores::update() {
	testFile();


	for (int setupNumbers = 0; setupNumbers < 10; setupNumbers++)
	{
		highscoreNumberArr[setupNumbers] = setupNumbers + 1;
	}
	string textFile = "";
	display = "";
	int allHighScoreCounter = 0;
	for (int k = 0; k < 10; k++)
	{
		display += to_string(highscoreNumberArr[k]) + " " + highscoreNameArr[k] + " " + to_string(highscoreScoreArr[k]) + "\n";
		allHighScoreCounter += 3;
	}
	cout << "High Scores: \n" << getHighscore();
}

Highscores::Highscores()
{
	testFile();


	for (int setupNumbers = 0; setupNumbers < 10; setupNumbers++)
	{
		highscoreNumberArr[setupNumbers] = setupNumbers + 1;
	}
	string textFile = "";
	display = "";
	int allHighScoreCounter = 0;
	for (int k = 0; k < 10; k++)
	{
		display += to_string(highscoreNumberArr[k]) + "            " + highscoreNameArr[k] + "                                                                                      " + to_string(highscoreScoreArr[k]) + "\n";
		allHighScoreCounter += 3;
	}
	cout << "High Scores: \n" << getHighscore();
}

Highscores::~Highscores()
{
}
