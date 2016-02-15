#include "Camera.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	if (Application::IsKeyPressed('W'))
	{
		position.y += 0.5f * static_cast<float>(dt);
	}
	if (Application::IsKeyPressed('A'))
	{
		position.x -= 0.5f * static_cast<float>(dt);
	}
	if (Application::IsKeyPressed('S'))
	{
		position.y -= 0.5f * static_cast<float>(dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		position.x += 0.5f * static_cast<float>(dt);
	}
	if (Application::IsKeyPressed(' '))
	{
		position.x = 4;
		position.y = 3;
		position.z = 3;
	}
}

Vector3 Camera::target = Vector3(0, 0, 0);