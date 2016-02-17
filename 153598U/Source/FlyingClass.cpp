#include "FlyingClass.h"
#include "Application.h"
#include <iostream>

Flying::Flying()
{
	activated = true;
	fuel = 100;
	gravity = 10;
	speed = 15;
}
Flying::~Flying()
{
}

void Flying::Fly(double dt, Camera5 &camera, Mesh** meshList)
{
	float fuelrate = 0.8;
	float rechargeRate = 0.4;
	float offset = 2;
	if (Application::IsKeyPressed(VK_SPACE) && fuel > 0 && activated == true)
	{
		if (camera.position.y + camera.position.Normalized().y * dt * speed + 1 < 498 && camera.position.y + camera.position.Normalized().y * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = SP2::GEO_LEFTWALL1; i < SP2::GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.y + camera.position.Normalized().y * dt * speed < meshList[i]->min->y ||
						camera.position.y + camera.position.Normalized().y * dt * speed > meshList[i]->max->y ||
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
						move = false;
						break;
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
				gravity = 10 * dt;
			}
		}
	}
	else
	{
		bool fall = false;
		for (int i = SP2::GEO_LEFTWALL1; i < SP2::GEO_TEXT; i++)
		{
			if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
			{
				if (camera.position.x  > meshList[i]->position.x + meshList[i]->min->x + offset - 3.8 &&
					camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset + 3.8 &&
					camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset - 3.8 &&
					camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset + 3.8
					)
				{
					if (camera.position.y - 6 - gravity > meshList[i]->position.y + meshList[i]->max->y)
					{
						fall = true;
					}
					else
					{
						fall = false;
						break;
					}
				}
				else
				{
					fall = true;
				}
			}
		}
		if (fall == true && camera.position.y - 5 - gravity > 0)
		{
			gravity += dt;
			camera.position.y -= gravity * 1.8;
		}
		else
		{
			gravity = 10 * dt;
		}
		if (fuel < 100)
		{
			fuel += rechargeRate;
			if (fuel > 60)
			{
				activated = true;
			}
			cout << "Increasing fuel rate: " << fuel << endl;
		}
	}
}