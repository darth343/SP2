#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Gun.h"

struct Inventory

{
public:
	Inventory(){
		TotalCash = 1000;
		ownRifle = true;
		ownSMG = false;
		ownPistol = false;
		Rifle.ammo = 10;
		SMG.ammo = 10;
		Pistol.ammo = 41;
	};
	~Inventory(){};
	
	Gun * GunSelected;
	int TotalCash;
	Gun Rifle;
	Gun SMG;
	Gun Pistol;
	bool ownRifle;
	bool ownSMG;
	bool ownPistol;


};







#endif