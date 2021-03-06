/****************************************************************************/
/*!
\file FlyingClass.cpp
\author Kenzo-Hari
\par email: 155113m\@mymail.nyp.edu.sg
\brief
Definition of all methods declared in FlyingClass.h
*/
/****************************************************************************/
#include "FlyingClass.h"
#include "Application.h"
#include <iostream>

/****************************************************************************/
/*!
\brief
Flying Constructor
Construct Flying Class by initializing boolean, fuel and speed
*/
/****************************************************************************/
Flying::Flying()
{
	activated = true;
	fuel = 100;
	speed = 15;
}

/****************************************************************************/
/*!
\brief
Flying deconstructor
Deconstructs Flying Class
*/
/****************************************************************************/
Flying::~Flying()
{
}

/****************************************************************************/
/*!
\brief
Method for using jetpacks
Method to take in min and max so that it cheks if the player is able to move or not
*/
/****************************************************************************/
void Flying::Fly(double dt, Camera5 &camera, Mesh** meshList, int start, int end, int height)
{
	float fuelrate = 0.8;
	float rechargeRate = 0.4;
	float offset = 2;
	if (Application::IsKeyPressed(VK_SPACE) && fuel > 0 && activated == true)
	{
		if (camera.position.y + camera.position.Normalized().y * dt * speed + 1 < 498 && camera.position.y + camera.position.Normalized().y * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = start; i < end; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (//camera.position.y + camera.position.Normalized().y * dt * speed < meshList[i]->min->y ||
						//camera.position.y + camera.position.Normalized().y * dt * speed > meshList[i]->max->y ||
						camera.position.x < meshList[i]->min->x + meshList[i]->position.x ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x ||
						camera.position.z < meshList[i]->min->z + meshList[i]->position.z ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z 
						)
					{
						move = true;
					}
					else
					{
						if (camera.position.y - height > meshList[i]->position.y + meshList[i]->max->y ||
							camera.position.y + 2 < meshList[i]->position.y + meshList[i]->min->y
							)
						{
							move = true;
						}
						else
						{
							move = false;
							break;
						}
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
			{
				fuel -= fuelrate;
				if (fuel <= 0)
				{
					activated = false;
				}
				camera.position.y += dt * speed;
			}
		}
	}
}