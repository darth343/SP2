#ifndef GUN_H_
#define GUN_H_



struct Gun
{
public:
	Gun(){ delayMultiplier = 0.3; semiAuto = false; reload = true; needAmmo = false; };
	~Gun(){};

	bool semiAuto;
	bool reload;
	bool needAmmo;
	float delayMultiplier;
	bool  shotOne;
	bool  shotTwo;
	bool  stopFiring;
	int ammo = 0;
	int clip = 0;

};




#endif