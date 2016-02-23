#ifndef PLAYER_H_
#define PLAYER_H_
#include "Inventory.h"

struct Player
{



public:
	Player(){ Health = 100; };
	~Player(){};

	Inventory inv;
	int Health;

};





#endif