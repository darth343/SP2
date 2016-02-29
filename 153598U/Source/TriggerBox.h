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
	TriggerBox(Vector3 mini, Vector3 maxi, Vector3 teleport, string text1, string text2, float size1, float size2, float x1, float y1, float x2, float y2) : minimum(mini), maximum(maxi), displayText1(text1), displayText2(text2), teleportLocation(teleport), textSize1(size1), textSize2(size2), x2(x2), y2(y2), x1(x1), y1(y1)
	{
		render = false;
		endTime = 0;
		runTime = 0;
		triggered = false;
	};
	~TriggerBox(){};

	void TriggerEvent(double dt, Camera5 &camera, double time);
	void renderTransition(MS ms, MS vs, MS ps, unsigned int m_parameters[25], Mesh * text, Mesh * screen);
	bool render;
	static bool rendering;
private:
	Vector3 minimum;
	Vector3 maximum;
	Vector3 teleportLocation;
	float x1;
	float y1;
	float x2;
	float y2;
	float textSize1;
	float textSize2;
	string displayText1;
	string displayText2;
	bool triggered;
	double endTime;
	double runTime;
};

#endif