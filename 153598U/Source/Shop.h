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
	void shopping(Inventory &inv ,int &points);
	bool openShop;
	bool buyRifle(Inventory &inv, int &points);
	bool buySMG(Inventory &inv,  int &points);
	bool buyPistol(Inventory &inv, int &points);
//	bool lookAtShop;
	Mesh* ShopInteraction(double dt, Camera5 camera, Mesh** meshList);

	
};




#endif 