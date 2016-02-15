//#include "GL\glew.h"
//#include "Movement.h"
//#include "shader.hpp"
//#include "Mtx44.h"
//#include "MeshBuilder.h"
//#include "LoadTGA.h"
//#include "Application.h"
//#include "Camera2.h"
//#include "Utility.h"
//
//
//void Movement::MovementCharac(double dt, Mesh ** meshList, Camera5 camera)
//{
//	int speed = 15;
//	float offset = 2;
//	int cameraX = -1;
//
//	if (Application::IsKeyPressed('W'))
//	{
//		//std::cout << "TEST" << std::endl;
//		if (camera.position.x + camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.view.Normalized().x * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.x + camera.view.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x + camera.view.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.x += camera.view.Normalized().x * dt * speed;
//		}
//		if (camera.position.y + camera.view.Normalized().y * dt * speed + 1 < 498 && camera.position.y + camera.view.Normalized().y * dt * speed - 1 > -498)
//		{
//			bool move = false;
//
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.z < meshList[i]->min->z ||
//						camera.position.z > meshList[i]->max->z ||
//						camera.position.x < meshList[i]->min->x ||
//						camera.position.x > meshList[i]->max->x
//						)
//					{
//						move = true;
//					}
//					else
//					{
//						if (Application::IsKeyPressed(VK_SPACE) &&
//							camera.position.y + camera.position.Normalized().y * dt * speed  < meshList[i]->min->y
//							)
//						{
//							move = true;
//						}
//					}
//				}
//
//				if (move && Application::IsKeyPressed(VK_SPACE))
//				{
//					camera.position.y += camera.position.Normalized().y * dt * speed;
//				}
//			}
//		}
//		if (camera.position.z + camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.view.Normalized().z * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						camera.position.z + camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.z + camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.z += camera.view.Normalized().z * dt * speed;
//		}
//	}
//	if (Application::IsKeyPressed('S'))
//	{
//		if (camera.position.x - camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.view.Normalized().x * dt * speed - 1 > -498)
//		{
//			bool move = false;
//
//
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.x -= camera.view.Normalized().x * dt * speed;
//		}
//		//if (camera.position.y - camera.view.Normalized().y * dt * speed + 1 < 498 && camera.position.y - camera.view.Normalized().y * dt * speed - 1 > -498)
//		//{
//		//	camera.position.y -= camera.view.Normalized().y * dt * speed;
//		//}
//		if (camera.position.z - camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.view.Normalized().z * dt * speed - 1 > -498)
//		{
//			bool move = false;
//
//
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						camera.position.z - camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.z - camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.z -= camera.view.Normalized().z * dt * speed;
//		}
//	}
//	if (Application::IsKeyPressed('A'))
//	{
//		if (camera.position.x - camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.right.Normalized().x * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.x - camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x - camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.x -= camera.right.Normalized().x * dt * speed;
//		}
//		//if (camera.position.y - camera.right.Normalized().y * dt * speed + 1 < 498 && camera.position.y - camera.right.Normalized().y * dt * speed - 1 > -498)
//		//{
//		//	camera.position.y -= camera.right.Normalized().y * dt * speed;
//		//}
//		if (camera.position.z - camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.right.Normalized().z * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						camera.position.z - camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.z - camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.z -= camera.right.Normalized().z * dt * speed;
//		}
//	}
//	if (Application::IsKeyPressed('D'))
//	{
//		if (camera.position.x + camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.right.Normalized().x * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.x + camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x + camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.x += camera.right.Normalized().x * dt * speed;
//		}
//		//if (camera.position.y + camera.right.Normalized().y * dt * speed + 1 < 498 && camera.position.y + camera.right.Normalized().y * dt * speed - 1 > -498)
//		//{
//		//	camera.position.y += camera.right.Normalized().y * dt * speed;
//		//}
//		if (camera.position.z + camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.right.Normalized().z * dt * speed - 1 > -498)
//		{
//			bool move = false;
//			for (int i = SP2::GEO_MODEL1; i < SP2::GEO_TEXT; i++)
//			{
//				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
//				{
//					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
//						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
//						camera.position.z + camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
//						camera.position.z + camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
//						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
//						0 > meshList[i]->max->y + meshList[i]->position.y + offset)
//						move = true;
//					else
//					{
//						move = false;
//						break;
//					}
//				}
//				else
//				{
//					move = true;
//				}
//			}
//			if (move)
//				camera.position.z += camera.right.Normalized().z * dt * speed;
//		}
//	}
//}