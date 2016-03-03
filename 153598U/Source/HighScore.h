/******************************************************************************/
/*!
\file	HighScore.h
\author Kenzo-Hari
\par	email: 155113m\@mymail.nyp.edu.sg
\brief
Class to define the HighScore
*/
/******************************************************************************/
#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using std::stringstream;
using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;

/******************************************************************************/
/*!
Class HighScore:
\brief	Defines the Highscore with its constructor, destructor, methods and functions
*/
/******************************************************************************/
class HighScore
{
public:
	HighScore(){};
	~HighScore(){};
/****************************************************************************/
/*!
Vector of Highscores
*/
/****************************************************************************/
	vector<int> data;
/****************************************************************************/
/*!
Initializes Vector of Highscores
*/
/****************************************************************************/
	void init();
};


#endif