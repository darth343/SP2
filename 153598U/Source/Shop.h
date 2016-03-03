#ifndef SHOP_H_
#define SHOP_H_
#include <string>
//#include "Player.h"
#include "Inventory.h"
#include"Mesh.h"
#include"Camera5.h"
using std::string;
/**************************************************************************************************/
/*!
\file     Shop.h
\author   Jeffrey Low Zheng Long
\par
\brief
struct for the shop
*/
/**************************************************************************************************/
struct Shop
{
public:
	/************************************************************************/
	/*!
	\brief A constructor for the Shop
	*/
	/***********************************************************************/
	Shop();
	/************************************************************************/
	/*!
	\brief A destructor for the shop
	*/
	/***********************************************************************/
	~Shop();
	/************************************************************************/
	/*!
	\brief A function for handling shopping purchases
	\param takes in a reference to the inv and points
	*/
	/***********************************************************************/
	void shopping(Inventory &inv ,int &points);
	/************************************************************************/
	/*!
	\brief A boolean for opening the shop
	*/
	/***********************************************************************/
	bool openShop;
	/************************************************************************/
	/*!
	\brief A boolean function that buys Rifle Ammo
	\param takes in a reference to inventory and points
	*/
	/***********************************************************************/
	bool buyRifle(Inventory &inv, int &points);

	/************************************************************************/
	/*!
	\brief A boolean function that buys SMG ammo
	\param takes in a reference to inventory and points
	*/
	/***********************************************************************/
	bool buySMG(Inventory &inv,  int &points);
	/************************************************************************/
	/*!
	\brief A boolean function that buys Pistol ammo
	\param takes in a reference to inventory and points
	*/
	/***********************************************************************/
	bool buyPistol(Inventory &inv, int &points);
	/************************************************************************/
	/*!
	\brief A function that identify a shop mesh
	\param takes in delta time,camera and mesh list
	*/
	/***********************************************************************/
	Mesh* ShopInteraction(double dt, Camera5 camera, Mesh** meshList);

	
};




#endif 