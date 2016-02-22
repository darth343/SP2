#include "Camera5.h"
#include "Application.h"
#include "Mtx44.h"
#include <Windows.h>
#include <iostream>

using std::cout;
using std::endl;

Vector3 Camera5::view = Vector3(0, 0, 0);
Vector3 Camera5::right = Vector3(0, 0, 0);

Camera5::Camera5()
{
}

Camera5::~Camera5()
{
}

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

void Camera5::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	const float mouseSpeed = 5;
	const int speed = 10;

	const int yFOV = 85;

	horiRot += mouseSpeed * dt * float(800 / 2 - Application::mouseX);
	if (vertRot + mouseSpeed * dt * float(600 / 2 - Application::mouseY) < yFOV && vertRot + mouseSpeed * dt * float(600 / 2 - Application::mouseY) > -yFOV)
		vertRot += mouseSpeed * dt * float(600 / 2 - Application::mouseY);

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

void Camera5::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}