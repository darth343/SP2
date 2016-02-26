#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Camera5.h"
#include "Mesh.h"
#include "FlyingClass.h"
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
	Flying jetPack;
	void MovementCharac(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
	void Gravity(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
private:
	float offset;
	float gravityMultiplier;
	float cameraHeight;
	float gravity;
	Vector3 prevPos;
};

#endif