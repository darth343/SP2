/****************************************************************************/
/*!
\file Camera5.cpp
\author Arun Ezekiel
\par email: 153598U\@mymail.nyp.edu.sg
\brief
Definition of all methods declared in Camera5.h
*/
/****************************************************************************/
#include "Camera5.h"
#include "Application.h"
#include "Mtx44.h"
#include <Windows.h>
#include <iostream>

using std::cout;
using std::endl;

/****************************************************************************/
/*!
\brief
Camera Constructor
*/
/****************************************************************************/
Camera5::Camera5()
{
}
/****************************************************************************/
/*!
\brief
Camera Destructor
*/
/****************************************************************************/
Camera5::~Camera5()
{
}
/****************************************************************************/
/*!
\brief
Camera5 Initializer
\param pos, target, up
Initialize Camera with a position, target, up
*/
/****************************************************************************/
void Camera5::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = Vector3(

		cos(Math::DegreeToRadian(0)) * sin(Math::DegreeToRadian(0)),

		sin(Math::DegreeToRadian(0)),

		cos(Math::DegreeToRadian(0)) * cos(Math::DegreeToRadian(0))
		);
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}
/****************************************************************************/
/*!
\brief
Camera5 Update Function
\param dt
Updates Camera with dt
*/
/****************************************************************************/
void Camera5::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	const float mouseSpeed = 5;
	const int speed = 10;

	const int yFOV = 85;

	horiRot += mouseSpeed * dt * float(1280 / 2 - Application::mouseX);
	if (vertRot + mouseSpeed * dt * float(720 / 2 - Application::mouseY) < yFOV && vertRot + mouseSpeed * dt * float(720 / 2 - Application::mouseY) > -yFOV)
		vertRot += mouseSpeed * dt * float(720 / 2 - Application::mouseY);

	view = Vector3(

		cos(Math::DegreeToRadian(vertRot)) * sin(Math::DegreeToRadian(horiRot)),

		sin(Math::DegreeToRadian(vertRot)),

		cos(Math::DegreeToRadian(vertRot)) * cos(Math::DegreeToRadian(horiRot))

		);
	target = position + view;
	// Right vector
	right = Vector3(
		sin(Math::DegreeToRadian(horiRot - 90)),
		0,
		cos(Math::DegreeToRadian(horiRot - 90)));

	up = right.Cross(view);
}
/****************************************************************************/
/*!
\brief
Overloaded Camera Update Function
\param dt, disableControls
Updates Camera Position with dt
*/
/****************************************************************************/
void Camera5::Update(double dt, bool disableControls)
{
	view = Vector3(

		cos(Math::DegreeToRadian(0)) * sin(Math::DegreeToRadian(0)),

		sin(Math::DegreeToRadian(0)),

		cos(Math::DegreeToRadian(0)) * cos(Math::DegreeToRadian(0))

		);
	target = position + view;

	// Right vector
	right = Vector3(
		sin(Math::DegreeToRadian(horiRot - 90)),
		0,
		cos(Math::DegreeToRadian(horiRot - 90)));

	up = right.Cross(view);
}

/****************************************************************************/
/*!
\brief
Camera Reset Function
Resets Position, target and up to default Values
*/
/****************************************************************************/
void Camera5::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}