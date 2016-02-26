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
using std::cout;
using std::endl;
using std::vector;


class Shooting 
{
public:
	struct TestBullet
	{
		Vector3 Position;
		Vector3 start;
		Vector3 trajectory;
	};

	Shooting();
	~Shooting();
	void ShootingBullets(Camera5 camera, double dt, float time,Mesh** meshList);
	void bulletHitDetection(vector<AI> &mobs, double dt, Camera5 camera);
	Mesh* Shootable(double dt, Camera5 camera, Mesh** meshList, vector<AI> &mobs);
	vector<TestBullet> bullets;
	//bool ifShootable; // when object get shot
	bool objectDied;//when object is dead
//	Mesh * shootable(double dt, Camera5 camera, Mesh ** meshList);
	float bulletspeed = 100;
	TestBullet tempMag;
	//Camera5 camera;
	float delay = 0;
	//float delayMultiplier = 0.1;
	Mesh * object;
	Gun Gun;
	Damage damage;
};




#endif