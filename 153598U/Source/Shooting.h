#ifndef SHOOTING_H_
#define SHOOTING_H_
#include <vector>
#include"Camera5.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Enemy.h"
#include <iostream>
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
	void bulletHitDetection(vector<enemy> &mobs, double dt, Camera5 camera);
	vector<TestBullet> bullets;
	bool shot; // when object get shot
	bool objectDied;//when object is dead
//	Mesh * shootable(double dt, Camera5 camera, Mesh ** meshList);
	float bulletspeed = 5;
	TestBullet tempMag;
	//Camera5 camera;
	float delay = 0;
	Mesh * object;
};




#endif