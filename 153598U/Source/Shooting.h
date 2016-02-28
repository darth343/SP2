#ifndef SHOOTING_H_
#define SHOOTING_H_
#include <vector>
#include"Camera5.h"
#include "Mesh.h"
#include "Vector3.h"
#include "AI.h"
#include <iostream>
#include "Gun.h"
#include "Damage.h"
#include "Player.h"
using std::cout;
using std::endl;
using std::vector;


class Shooting 
{
public:
	struct Bullet
	{
		Vector3 Position;
		Vector3 start;
		Vector3 trajectory;
	};

	Shooting();
	~Shooting();
	void ShootingBullets(Camera5 camera, double dt, float time,Mesh** meshList, Player &player);
	void bulletHitDetection(vector<AI> &mobs, double dt, Camera5 camera);
	vector<Bullet> bullets;
	float bulletspeed;
	float delay;
	//bool GunFiring;
	//bool JetFiring;
};




#endif