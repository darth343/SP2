#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "Gun.h"

struct Inventory

{
public:
	Inventory(){
	//	TotalCash = 1000;
		ownRifle = true;
		ownSMG = false;
		ownPistol = false;
		Rifle.ammo = 90;
		Rifle.clip = 30;
		SMG.ammo = 90;
		SMG.clip = 30;
		Pistol.ammo = 100;
		Pistol.clip = 10;
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