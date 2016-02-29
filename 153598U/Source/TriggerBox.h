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
public:
	TriggerBox(){};
	TriggerBox(Vector3 mini, Vector3 maxi, string text) : minimum(mini), maximum(maxi), displayText(text) 
	{
		textSize = 1;
		x = 40;
		y = 30;
	};
	~TriggerBox(){};

	void TriggerEvent(double dt, Camera5 &camera, Vector3 teleportLocation, double time);
	void renderTransition(MS ms, MS vs, MS ps, unsigned int m_parameters[25], Mesh * text, Mesh * screen);
	static bool render;
private:
	Vector3 minimum;
	Vector3 maximum;
	float x;
	float y;
	float textSize;
	string displayText;
	bool triggered;
	double endTime;
	double runTime;
};

#endif