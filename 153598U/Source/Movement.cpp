#include "Movement.h"
#include "Application.h"
void Movement::MovementCharac(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End)
{
	int speed = 50;
	float offset = 2;
	int cameraX = -1;
	if (Application::IsKeyPressed('W'))
	{
		if (camera.position.x + camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||  //Check min and max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset || //Check max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset || //Check min for x axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset || //Check max for x axis. If bigger than min, smaller than max, walk = false 
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset >= meshList[i]->max->y + meshList[i]->position.y + offset)
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
				camera.position.x += camera.view.Normalized().x * dt * speed;
		}

		if (camera.position.z + camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.view.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.z += camera.view.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		if (camera.position.x - camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;


			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.x -= camera.view.Normalized().x * dt * speed;
		}

		if (camera.position.z - camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.view.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;


			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z - camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z - camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset> meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.z -= camera.view.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('A'))
	{
		if (camera.position.x - camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.right.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x - camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x - camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.x -= camera.right.Normalized().x * dt * speed;
		}

		if (camera.position.z - camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.right.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z - camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z - camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset> meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.z -= camera.right.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		if (camera.position.x + camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.right.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x + camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x + camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.x += camera.right.Normalized().x * dt * speed;
		}

		if (camera.position.z + camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.right.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z + camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z + camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.z += camera.right.Normalized().z * dt * speed;
		}
	}
	jetPack.Fly(dt, camera, meshList, Start, End);
	Gravity(dt, camera, meshList, Start, End);
}
void Movement::MovementRunner(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End)
{
	int speed = 70;
	float offset = 2;

		if (camera.position.x + camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||  //Check min and max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset || //Check max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset || //Check min for x axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset || //Check max for x axis. If bigger than min, smaller than max, walk = false 
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset >= meshList[i]->max->y + meshList[i]->position.y + offset)
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
				camera.position.x += camera.view.Normalized().x * dt * speed;
		}

		if (camera.position.z + camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.view.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = Start; i < End; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
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
				camera.position.z += camera.view.Normalized().z * dt * speed;
		}
		if (Application::IsKeyPressed('A'))
		{
			if (camera.position.x - camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.right.Normalized().x * dt * speed - 1 > -498)
			{
				bool move = false;
				for (int i = Start; i < End; i++)
				{
					if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
					{
						if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
							camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
							camera.position.x - camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
							camera.position.x - camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
							camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
							camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
							move = true;
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
					camera.position.x -= camera.right.Normalized().x * dt * speed;
			}

			if (camera.position.z - camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.right.Normalized().z * dt * speed - 1 > -498)
			{
				bool move = false;
				for (int i = Start; i < End; i++)
				{
					if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
					{
						if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
							camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
							camera.position.z - camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
							camera.position.z - camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
							camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
							camera.position.y - 5 + offset> meshList[i]->max->y + meshList[i]->position.y + offset)
							move = true;
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
					camera.position.z -= camera.right.Normalized().z * dt * speed;
			}
		}
		if (Application::IsKeyPressed('D'))
		{
			if (camera.position.x + camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.right.Normalized().x * dt * speed - 1 > -498)
			{
				bool move = false;
				for (int i = Start; i < End; i++)
				{
					if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
					{
						if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
							camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
							camera.position.x + camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
							camera.position.x + camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
							camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
							camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
							move = true;
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
					camera.position.x += camera.right.Normalized().x * dt * speed;
			}

			if (camera.position.z + camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.right.Normalized().z * dt * speed - 1 > -498)
			{
				bool move = false;
				for (int i = Start; i < End; i++)
				{
					if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
					{
						if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
							camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
							camera.position.z + camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
							camera.position.z + camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
							camera.position.y < meshList[i]->min->y + meshList[i]->position.y - offset ||
							camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
							move = true;
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
					camera.position.z += camera.right.Normalized().z * dt * speed;
			}
		}
		Gravity(dt, camera, meshList, Start, End);
	}
void Movement::Gravity(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End)
{
	float fuelrate = 0.8;
	float rechargeRate = 0.4;
	float offset = 2;
	if (!Application::IsKeyPressed(VK_SPACE))
	{
		bool fall = false;
		for (int i = Start; i < End; i++)
		{
			if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
			{
				if (camera.position.x  > meshList[i]->position.x + meshList[i]->min->x + offset - 3.8 &&
					camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset + 3.8 &&
					camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset - 3.8 &&
					camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset + 3.8
					)
				{
					if (camera.position.y - 5 - (gravity + dt * 1.8)> meshList[i]->position.y + meshList[i]->max->y)
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
		if (fall == true)
		{
			bool wallrunning = false;
			gravity += dt * 1.8;
			for (int i = Start; i < End; i++)
			{
				if (
					(camera.right.x + camera.position.x > meshList[i]->position.x + meshList[i]->min->x + offset - 3.8&&
					camera.right.x + camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset + 3.8 &&
					camera.right.z + camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset - 3.8 &&
					camera.right.z + camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset + 3.8&&
					camera.right.y + camera.position.y > meshList[i]->position.y + meshList[i]->min->y &&
					camera.right.y + camera.position.y < meshList[i]->position.y + meshList[i]->max->y) ||
					(
					-camera.right.x + camera.position.x > meshList[i]->position.x + meshList[i]->min->x + offset - 3.8&&
					-camera.right.x + camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset + 3.8 &&
					-camera.right.z + camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset - 3.8 &&
					-camera.right.z + camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset + 3.8&&
					-camera.right.y + camera.position.y > meshList[i]->position.y + meshList[i]->min->y &&
					-camera.right.y + camera.position.y < meshList[i]->position.y + meshList[i]->max->y
					)
					)
				{
					cout << "TO THE WALL" << endl;
					wallrunning = true;
					break;
				}
			}
			if (wallrunning == false || prevPos == camera.position)
			{
				camera.position.y -= gravity;
			}
			else
			{
				camera.position.y -= gravity/25;
			}
			prevPos = camera.position;
		}
		else
		{
			gravity = 10 * dt;
		}
		if (jetPack.fuel < 100)
		{
			jetPack.fuel += rechargeRate;
			if (jetPack.fuel > 60)
			{
				jetPack.activated = true;
			}
		}
	}
}