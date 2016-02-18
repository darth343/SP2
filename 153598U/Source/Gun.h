#ifndef GUN_H_
#define GUN_H_



struct Gun
{
public:
	Gun(){delayMultiplier = 0.3; semiAuto = false;};
	~Gun(){};

	bool semiAuto;
	float delayMultiplier;
	bool  shotOne;
	bool  shotTwo;
	bool  stopFiring;


};




#endif