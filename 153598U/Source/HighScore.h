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


class HighScore
{
public:
	HighScore(){};
	~HighScore(){};
	vector<int> data;
	void init();
};


#endif