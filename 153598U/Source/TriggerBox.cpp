#include "TriggerBox.h"
#include "Vertex.h"
#include "SP2.h"
bool TriggerBox::render = false;
void TriggerBox::TriggerEvent(double dt, Camera5 &camera, Vector3 teleportLocation, double time)
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
	if (triggered)
	{
		if (runTime < endTime)
		{
			runTime += dt;
			render = true;
			camera.position = teleportLocation;
		}
		else
		{
			render = false;
			triggered = false;
		}
	}
}

void TriggerBox::renderTransition(MS ms, MS vs, MS ps, unsigned int m_parameters[25], Mesh * text, Mesh * screen)
{
	string test = "Aksks";
	if (render)
	{
		cout << "rendering" << endl;
		SP2::RenderOBJonScreen(screen, 100, 100, 40, 30, ms, vs, ps, m_parameters);
		SP2::RenderTextOnScreen(text, test , Color(1, 1, 1), textSize, 40 - (test.size()/2), 20, ms, vs, ps, m_parameters);
	}
}