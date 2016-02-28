#include "TriggerBox.h"

void TriggerBox::TriggerEvent(double dt, Camera5 &camera, Vector3 teleportLocation, double time)
{
	if (!triggered)
	{
		endTime = time + 5;
		runTime = time;
		triggered = true;
	}
	if (runTime < endTime)
	{
		runTime += dt;
	}
}