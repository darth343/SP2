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
		Rifle.ammo = 100;
		SMG.ammo = 10;
		Pistol.ammo = 41;
		SMG.delayMultiplier = 0.1;
		Pistol.delayMultiplier = 0.7;
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