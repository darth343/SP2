#ifndef GUN_H_
#define GUN_H_



struct Gun
{
public:
	Gun()
	{
		delayMultiplier = 0.3; semiAuto = false;
		stopFiring = false;
	};
	~Gun(){};

	bool semiAuto;
	float delayMultiplier;
	bool stopFiring;
	bool  shotOne;
	bool  shotTwo;
	int ammo = 0;

};




#endif