#ifndef ENEMY_H
#define ENEMY_H
#include "Mesh.h"
#include "Camera5.h"

class enemy
{
public:
	enemy() { enemyDamage = 5; };
	~enemy() {};
	float health;
	int enemyHit(double dt, Camera5 camera, Mesh** meshList);
	int enemyDamage;
	Mesh* enemyMesh;
};

#endif