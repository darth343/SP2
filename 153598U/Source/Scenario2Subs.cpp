#include "Scenario2Subs.h"
#include <iostream>
void Scenario2_Subtitles::init(double time)
{
	if (initialized == false)
	{
		subtitles temp;
		temp.runTime = time ;
		temp.endTime = time + 3;
		temp.sub = "You killed all the Aliens! Now we can extract you safely";
		allSubs.push_back(temp);

		temp.runTime = time + 4;
		temp.endTime = time + 7;
		temp.sub = "Go to the BLACK pillar for extraction";
		allSubs.push_back(temp);
		initialized = true;
	}
}

void Scenario2_Subtitles::run(double dt)
{
	if (allSubs.size() > 0)
	{
		if (allSubs[0].runTime < allSubs[0].endTime)
		{
			allSubs[0].runTime += dt;
			render = true;
		}
		else
		{
			allSubs.erase(allSubs.begin());
			render = false;
		}
	}
}