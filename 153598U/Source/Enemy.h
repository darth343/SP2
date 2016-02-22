#ifndef ENEMY_H
#define ENEMY_H
#include "Mesh.h"

class enemy
{
public:
	enemy() {};
	~enemy() {};
	float health;
	Mesh* EnemyMesh;
};

#endif