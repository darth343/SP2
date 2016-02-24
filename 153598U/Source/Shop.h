#ifndef SHOP_H_
#define SHOP_H_
#include <string>
//#include "Player.h"
#include "Inventory.h"
#include"Mesh.h"
#include"Camera5.h"
using std::string;

struct Shop
{
public:
	Shop();
	~Shop();
	void shopping(Inventory &inv);
	bool openShop;
	bool buyRifle(Inventory &inv);
	bool buySMG(Inventory &inv);
	bool buyPistol(Inventory &inv);
//	bool lookAtShop;
	Mesh* ShopInteraction(double dt, Camera5 camera, Mesh** meshList);

	string shopChoices1;
	string shopChoices2;
	string shopChoices3;


	
};




#endif 