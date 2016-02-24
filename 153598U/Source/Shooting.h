#ifndef SHOOTING_H_
#define SHOOTING_H_
#include <vector>
#include"Camera5.h"
#include "Mesh.h"
#include "Vector3.h"
#include "Enemy.h"
#include <iostream>
#include "Gun.h"
#include "Damage.h"
//#include "Inventory.h"
#include "Player.h"
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
	void ShootingBullets(Camera5 camera, double dt, float time, Mesh** meshList,Player &player);
	void bulletHitDetection(vector<enemy> &mobs, double dt, Camera5 camera);
	Mesh* Shootable(double dt, Camera5 camera, Mesh** meshList, vector<enemy> &mobs);
	vector<TestBullet> bullets;
	bool objectDied;//when object is dead
	float bulletspeed = 5;
	TestBullet tempMag;
	float delay = 0;
	Mesh * object;
	//Gun Gun;
	Damage damage;
	Player player;
	//Inventory inv;
};




#endif