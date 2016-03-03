/****************************************************************************/
/*!
\brief
Alien Movement Function
\param camera, meshList, dt, player
Updates all Alien position based on next position in path
*/
/****************************************************************************/
#ifndef TRIGGERBOX_H
#define TRIGGERBOX_H
#include "Vector3.h"
#include "Camera5.h"
/******************************************************************************/
/*!
\file	TriggerBox.h
\author Arun Ezekiel
\par	email: 153598U\@mymail.nyp.edu.sg
\brief
Class to define TriggerBoxes
*/
/******************************************************************************/
#include "Mesh.h"
#include "MatrixStack.h"
#include <string>
using std::string;
/****************************************************************************/
/*!
Class TriggerBox:
\brief Defines TriggerBox with functions and variables
*/
/****************************************************************************/
class TriggerBox
{
public:
	/****************************************************************************/
	/*!
	Defautl Constructors
	*/
	/****************************************************************************/
	TriggerBox(){};
	/****************************************************************************/
	/*!
	Overloaded Constructors
	*/
	/****************************************************************************/
	TriggerBox(Vector3 mini, Vector3 maxi, Vector3 teleport, string text1, string text2, float size1, float size2, float x1, float y1, float x2, float y2) : minimum(mini), maximum(maxi), displayText1(text1), displayText2(text2), teleportLocation(teleport), textSize1(size1), textSize2(size2), x2(x2), y2(y2), x1(x1), y1(y1)
	{
		render = false;
		endTime = 0;
		runTime = 0;
		triggered = false;
	};
	~TriggerBox(){};
	/****************************************************************************/
	/*!
	Returns the current runtime of the TriggerBox
	*/
	/****************************************************************************/
	double getRunTime() { return runTime; };
	/****************************************************************************/
	/*!
	TriggerEvent Function
	*/
	/****************************************************************************/
	bool TriggerEvent(double dt, Camera5 camera, double time);
	/****************************************************************************/
	/*!
	TriggerEvent Function
	*/
	/****************************************************************************/
	bool renderTransition(double dt, Camera5 &camera, MS ms, MS vs, MS ps, unsigned int m_parameters[25], Mesh * text, Mesh * screen);
	/****************************************************************************/
	/*!
	Boolean to check if Trigger Box started rendering
	*/
	/****************************************************************************/
	bool render;
	/****************************************************************************/
	/*!
	Boolean to check if ANY triggerBox is being rendered
	*/
	/****************************************************************************/
	static bool rendering;
	/****************************************************************************/
	/*!
	Boolean to check if Event has been triggered
	*/
	/****************************************************************************/
	bool triggered;
private:
	/****************************************************************************/
	/*!
	Vector3 that stores minimum position of trigger box
	*/
	/****************************************************************************/
	Vector3 minimum;
	/****************************************************************************/
	/*!
	Vector3 that stores maximum position of trigger box
	*/
	/****************************************************************************/
	Vector3 maximum;
	/****************************************************************************/
	/*!
	Vector3 that stores location to move the camera to
	*/
	/****************************************************************************/
	Vector3 teleportLocation;
	/****************************************************************************/
	/*!
	float to store coordinate X coordinate of first string
	*/
	/****************************************************************************/
	float x1;
	/****************************************************************************/
	/*!
	float to store coordinate Y coordinate of first string
	*/
	/****************************************************************************/
	float y1;
	/****************************************************************************/
	/*!
	float to store coordinate X coordinate of second string
	*/
	/****************************************************************************/
	float x2;
	/****************************************************************************/
	/*!
	float to store coordinate Y coordinate of second string
	*/
	/****************************************************************************/
	float y2;
	/****************************************************************************/
	/*!
	float to store scale size of first string
	*/
	/****************************************************************************/
	float textSize1;
	/****************************************************************************/
	/*!
	float to store scale size of second string
	*/
	/****************************************************************************/
	float textSize2;
	/****************************************************************************/
	/*!
	string to store first string
	*/
	/****************************************************************************/
	string displayText1;
	/****************************************************************************/
	/*!
	string to store second string
	*/
	/****************************************************************************/
	string displayText2;
	/****************************************************************************/
	/*!
	double to store time that trigger ends
	*/
	/****************************************************************************/
	double endTime;
	/****************************************************************************/
	/*!
	double to store current time trigger is running 
	*/
	/****************************************************************************/
	double runTime;
};

#endif