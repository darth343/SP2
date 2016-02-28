#ifndef TRIGGERBOX_H
#define TRIGGERBOX_H
#include "Vector3.h"
#include "Camera5.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include <string>
using std::string;

class TriggerBox
{
	TriggerBox(Vector3 minimum, Vector3 maximum, string text) : min(minimum), max(maximum), displayText(text)
	{};
	~TriggerBox() {};

	Vector3 min;
	Vector3 max;
	string displayText;
	bool triggered;
	double endTime;
	double runTime;
	void TriggerEvent(double dt, Camera5 &camera, Vector3 teleportLocation, double time);
};

#endif