#ifndef COINS_H
#define COINS_H
#include <vector>
#include "Mesh.h"
#include "Camera5.h"
class coins
{
public:
	coins(){};
	~coins(){};
	std::vector<Mesh *> allCoins;

	void init();
	void pickup(Camera5 camera);
	int acquired = 0;
	float rotateAngle = 0;
};
#endif