#ifndef FLYINGCLASS_H
#define FLYINGCLASS_H
#include "Camera5.h"
#include "Mesh.h"

class Flying
{
public:
	Flying();
	~Flying();
	void Fly(double dt, Camera5 &camera, Mesh ** meshList, int start, int end, int height);
	float getFuel() { return fuel; };
	float getStatus() { return activated; };
	float fuel;
	bool activated;
private:
	float speed;
};

#endif