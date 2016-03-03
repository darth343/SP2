#include "Shop.h"
#include "Application.h"

#include <iostream>
/**************************************************************************************************/
/*!
\file     Shop.cpp
\author   Jeffrey Low Zheng Long
\par
\brief
Functions for the shop
*/
/**************************************************************************************************/






/************************************************************************/
/*!
\brief A constructor for the Shop and for initialising
*/
/***********************************************************************/
Shop::Shop()
{
	openShop = false;
}
/************************************************************************/
/*!
\brief A destructor for the shop
*/
/***********************************************************************/
Shop::~Shop()
{

}

/************************************************************************/
/*!
\brief A function for handling shopping purchases
\param takes in a reference to the inv and points
*/
/***********************************************************************/
void Shop::shopping(Inventory &inv, int &points)
{
	buyRifle(inv,points);
	buySMG(inv,points);
	buyPistol(inv,points);
}

/************************************************************************/
/*!
\brief A function that identify a shop mesh
\param takes in delta time,camera and mesh list
*/
/***********************************************************************/
Mesh* Shop::ShopInteraction(double dt, Camera5 camera, Mesh** meshList)
{

	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range; temp += camera.view.Normalized())
	{
	
		/*for (int i = SP2::GEO_STORE;  i < SP2::GEO_TEXT; i++)
		{*/
			if (meshList[SP2::GEO_STORE]->min != nullptr || meshList[SP2::GEO_STORE]->max != nullptr)
			{	//std::cout << "TEST" << std::endl;
				if ((temp.x + camera.position.x <= meshList[SP2::GEO_STORE]->max->x + meshList[SP2::GEO_STORE]->position.x + offset && temp.x + camera.position.x >= meshList[SP2::GEO_STORE]->min->x + meshList[SP2::GEO_STORE]->position.x - offset) //Check min and max for x
					&& (temp.y + camera.position.y <= meshList[SP2::GEO_STORE]->max->y + meshList[SP2::GEO_STORE]->position.y + offset && temp.y + camera.position.y >= meshList[SP2::GEO_STORE]->min->y + meshList[SP2::GEO_STORE]->position.y - offset) //Check min and max for y
					&& (temp.z + camera.position.z <= meshList[SP2::GEO_STORE]->max->z + meshList[SP2::GEO_STORE]->position.z + offset && temp.z + camera.position.z >= meshList[SP2::GEO_STORE]->min->z + meshList[SP2::GEO_STORE]->position.z - offset)) //Check min and max for z
				{
					if (meshList[SP2::GEO_STORE]->lookAtShop == false)
					{
						return nullptr;
						break;
					}
					else
					{
						return meshList[SP2::GEO_STORE];
						break;
					}
				//}
			}
		}
	}
	//meshList[SP2::GEO_STORE]->lookAtShop = false;
	return nullptr;
}
/************************************************************************/
/*!
\brief A boolean function that buys Rifle Ammo
\param takes in a reference to inventory and points
*/
/***********************************************************************/
bool Shop::buyRifle(Inventory &inv, int &points)
{

	if (Application::IsKeyPressed('1') && inv.Rifle.ammo <400 && points>=50)
	{
		inv.Rifle.ammo = 400;
		cout << "bought Rifle,ammo: "<<inv.Rifle.ammo << endl;
		points-= 50;
		cout << "Total Cash: " << points << endl;
		return true;
	}
	else
		return false;
}
/************************************************************************/
/*!
\brief A boolean function that buys SMG ammo
\param takes in a reference to inventory and points
*/
/***********************************************************************/

bool Shop::buySMG(Inventory &inv, int &points)
{
	if (Application::IsKeyPressed('2') && inv.SMG.ammo < 600 && points>=35)
	{
		inv.SMG.ammo = 600;
		cout << "bought SMG,ammo: " << inv.SMG.ammo << endl;
		points -= 35;
		cout << "Total Cash: " << points << endl;
		return true;
	}
	else
		return false;
}

/************************************************************************/
/*!
\brief A boolean function that buys Pistol ammo
\param takes in a reference to inventory and points
*/
/***********************************************************************/
bool Shop::buyPistol(Inventory &inv, int &points)
{
	if (Application::IsKeyPressed('3') && inv.Pistol.ammo < 90 && points>=20)
	{
		inv.Pistol.ammo = 90;
		cout << "bought Pistol,ammo: "<<inv.Pistol.ammo << endl;
		points -= 20;
		cout << "Total Cash: " << points << endl;
		return true;
	}
	else
		return false;
}