#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "Camera5.h"
#include "Mesh.h"
#include "FlyingClass.h"
class Movement
{
public:
	Movement(){};
	~Movement(){};
	Flying jetPack;
	bool allowInput;
	void MovementCharac(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
	void MovementRunner(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
	void Gravity(double dt, Camera5 &camera, Mesh ** meshList, int Start, int End);
private:
	float gravity = 10;
	Vector3 prevPos;
};

#endif