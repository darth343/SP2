/****************************************************************************/
/*!
\file HighScore.cpp
\author Kenzo-Hari
\par email: 155113m\@mymail.nyp.edu.sg
\brief
Definition of all methods declared in Highscore.h
*/
/****************************************************************************/
#include "HighScore.h"

/****************************************************************************/
/*!
\brief
Method to initialize HighScore
Pushing in data when file is opened
*/
/****************************************************************************/
void HighScore::init()
{
	ifstream file;
	file.open("Scores//HighScore.txt");
	string temp;
	int score;
	while (getline(file, temp))
	{
		stringstream(temp) >> score;
		data.push_back(score);
	}
}