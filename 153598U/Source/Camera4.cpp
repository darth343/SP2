#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"
#include <Windows.h>
#include <iostream>

using std::cout;
using std::endl;

Camera4::Camera4()
{
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera4::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	const float mouseSpeed = 5;
	const int speed = 50;
	horiRot += mouseSpeed * dt * float(800 / 2 - Application::mouseX);
	vertRot += mouseSpeed * dt * float(600 / 2 - Application::mouseY);

	Vector3 view = Vector3(

	cos(Math::DegreeToRadian(vertRot)) * sin(Math::DegreeToRadian(horiRot)),

	sin(Math::DegreeToRadian(vertRot)),

	cos(Math::DegreeToRadian(vertRot)) * cos(Math::DegreeToRadian(horiRot))
	);

	
	target = position + view.Normalized();

	// Right vector
	Vector3 right = Vector3(
		sin(Math::DegreeToRadian(horiRot - 90)),
		0,
		cos(Math::DegreeToRadian (horiRot - 90)));

	up = right.Cross(view);


	if (Application::IsKeyPressed('W'))
	{
		position += view * dt * speed;
	}
	if (Application::IsKeyPressed('S'))
	{
		position -= view * dt * speed;
	}
	if (Application::IsKeyPressed('A'))
	{
		position -= right * dt * speed;
	}
	if (Application::IsKeyPressed('D'))
	{
		position += right * dt * speed;
	}
	if (Application::IsKeyPressed(' '))
	{
		position.y += dt * speed / 2;
	}
	if (Application::IsKeyPressed(VK_SHIFT))
	{
		position.y -= dt * speed / 2;
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		position.y += dt * speed / 2;
	}
	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera4::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}