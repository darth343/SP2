#ifndef SHOP_H_
#define SHOP_H_
#include <string>
#include "Player.h"
#include"Mesh.h"
#include"Camera5.h"
using std::string;

struct Shop
{
public:
	Shop();
	~Shop();
	void shopping(Player &player);
	bool openShop;
	bool buyRifle(Player &player);
	bool buySMG(Player &player);
	bool buyPistol(Player &player);
//	bool lookAtShop;
	Mesh* ShopInteraction(double dt, Camera5 camera, Mesh** meshList);

	string shopChoices1;
	string shopChoices2;
	string shopChoices3;


	
};




#endif 