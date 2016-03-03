/****************************************************************************/
/*!
\file TriggerBox.cpp
\author Arun Ezekiel
\par email: 153598U\@mymail.nyp.edu.sg
\brief
Definition of all methods declared in TriggerBox.h
*/
/****************************************************************************/
#include "TriggerBox.h"
#include "Vertex.h"
#include "SP2.h"
bool TriggerBox::rendering = false;
/****************************************************************************/
/*!
\brief
TriggerEvent Function
\param dt, camera, time
Checks if Camera if within minimum and maximum position, returns true if it does
*/
/****************************************************************************/
bool TriggerBox::TriggerEvent(double dt, Camera5 camera, double time)
{
	if (
		(camera.position.x > minimum.x && camera.position.x < maximum.x) &&
		(camera.position.y > minimum.y && camera.position.y < maximum.y) &&
		(camera.position.z > minimum.z && camera.position.z < maximum.z)
		)
	{
		if (!triggered)
		{
			endTime = time + 5;
			runTime = time;
			triggered = true;
		}
	}
	return triggered;
}
/****************************************************************************/
/*!
\brief
Render Transition
\param time, camera, ms, vs, ps, m_parameters[25], text, screen
Renders Strings and Black Screen on screen and moves camera to teleportLocation
*/
/****************************************************************************/
bool TriggerBox::renderTransition(double time, Camera5 &camera, MS ms, MS vs, MS ps, unsigned int m_parameters[25], Mesh * text, Mesh * screen)
{
	if (triggered)
	{
		if (runTime < endTime)
		{
			runTime = time;
			render = true;
			rendering = true;
			camera.position = teleportLocation;
			camera.horiRot = 0;
			camera.vertRot = 0;
		}
		else
		{
			render = false;
			rendering = false;
			triggered = false;
		}
	}
	if (render)
	{
		SP2::RenderOBJonScreen(screen, 100, 100, 40, 30, ms, vs, ps, m_parameters);
		SP2::RenderTextOnScreen(text, displayText1, Color(1, 1, 1), textSize1, x1, y1, ms, vs, ps, m_parameters);
		SP2::RenderTextOnScreen(text, displayText2, Color(1, 1, 1), textSize2, x2, y2, ms, vs, ps, m_parameters);
	}
	return render;
}