#include "HighScore.h"

void HighScore::init()
{
	ifstream file;
	file.open("Scores//HighScore.txt");
	string temp;
	int score;
	while (getline(file,temp))
	{
		stringstream(temp) >> score;
		data.push_back(score);
	}
}