#ifndef DAMAGE_H_
#define DAMAGE_H_

#include "Mesh.h"
#include "Shooting.h"

struct Damage
{
	Damage()
	{
		damageMultiplier = 1; 
	};
	~Damage(){};
	float damageMultiplier;
	Mesh mesh;
	bool headShot;
	bool normalShot;
	bool legShot;
};




#endif