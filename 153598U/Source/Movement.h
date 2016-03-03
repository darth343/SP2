/******************************************************************************/
/*!
\file	Movement.h
\author Kenzo-Hari
\par	email: 155113m\@mymail.nyp.edu.sg
\brief
Class to define the Movement of Character
*/
/******************************************************************************/
#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Camera5.h"
#include "Mesh.h"
#include "FlyingClass.h"

/****************************************************************************/
/*!
Class Movement:
\brief Defines a Movement with the class and ithe methods and functions
*/
/****************************************************************************/
class Movement
{
public:
	Movement()
	{
		offset = 2;
		cameraHeight = 10;
		gravity = 10;
		gravityMultiplier = 5;
	};
	~Movement(){};
/****************************************************************************/
/*!
Flying class for jetpack
*/
/****************************************************************************/
	Flying jetPack;
/****************************************************************************/
/*!
Boolean to switch between original controls to rainbow road controls
*/
/****************************************************************************/
	bool allowInput;
/****************************************************************************/
/*!
Method for Character's Movement in Survival Arena and Obstacel course
*/
/****************************************************************************/
	void MovementCharac(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
/****************************************************************************/
/*!
Method for Character's Movement in Rainbow Run Scenario
*/
/****************************************************************************/
	void MovementRunner(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
/****************************************************************************/
/*!
Method for "Gravity" affecting player
*/
/****************************************************************************/
	void Gravity(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
private:
/****************************************************************************/
/*!
Collision Offset
*/
/****************************************************************************/
	float offset;
/****************************************************************************/
/*!
Change in gravty when player falling etc.
*/
/****************************************************************************/
	float gravityMultiplier;
/****************************************************************************/
/*!
Heigh of the Player
*/
/****************************************************************************/
	float cameraHeight;
/****************************************************************************/
/*!
Default gravity
*/
/****************************************************************************/
	float gravity;
	Vector3 prevPos;
};

#endif