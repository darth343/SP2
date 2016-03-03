#ifndef PLAYER_H_
#define PLAYER_H_
#include "Inventory.h"
#include "Mesh.h"
#include "Camera5.h"
#include "Shop.h"
struct Player
{
public:
	Player(){ Health = 100; };
	~Player(){};

	void currentItems(double dt,Camera5 camera,Mesh** meshList);
	bool isDead();
	float getScaleHealth();
	int points=50;	
	Inventory inv;
	float Health;
	Mesh* object;
	Shop shop;
	float delay = 0;
	float time = 0;
	//int points=0;
	

};





#endif