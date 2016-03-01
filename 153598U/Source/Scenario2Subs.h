#ifndef SUBS_H
#define SUBS_H
#include <vector>
#include <string>
using std::string;
using std::vector;

struct subtitles
{
	double endTime;
	double runTime;

	string sub;
};

struct Scenario2_Subtitles
{
	bool initialized = false;
	bool render = false;
	void init(double time);
	void run(double dt);
	vector<subtitles> allSubs;
};

#endif