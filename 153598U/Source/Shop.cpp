#include "Shop.h"
#include "Application.h"

#include <iostream>
Shop::Shop()
{
	openShop = false;
	shopChoices1 = "Press 1 to buy a Rifle(200 Dollars)";
	shopChoices2 = "Press 2 to buy a SMG(150 Dollars)";
	shopChoices3 = "Press 3 to buy a Pistol(50 Dollars)";
}
Shop::~Shop()
{

}
void Shop::shopping(Inventory &inv)
{
	buyRifle(inv);
	buySMG(inv);
	buyPistol(inv);
}
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
	return nullptr;

}
bool Shop::buyRifle(Inventory &inv)
{

	if (Application::IsKeyPressed('1') && inv.Rifle.ammo <400 && inv.TotalCash >= 500)
	{
		inv.Rifle.ammo = 400;
		cout << "bought Rifle,ammo: "<<inv.Rifle.ammo << endl;
		inv.TotalCash -= 500;
		cout << "Total Cash: " << inv.TotalCash << endl;
		return true;
	}
	else
		return false;
}
bool Shop::buySMG(Inventory &inv)
{
	if (Application::IsKeyPressed('2') && inv.SMG.ammo < 600 && inv.TotalCash >= 300)
	{
		inv.SMG.ammo = 600;
		cout << "bought SMG,ammo: " << inv.SMG.ammo << endl;
		inv.TotalCash -= 100;
		cout << "Total Cash: " << inv.TotalCash << endl;
		return true;
	}
	else
		return false;
}
bool Shop::buyPistol(Inventory &inv)
{
	if (Application::IsKeyPressed('3') && inv.Pistol.ammo < 90 && inv.TotalCash >= 100)
	{
		inv.Pistol.ammo = 90;
		cout << "bought Pistol,ammo: "<<inv.Pistol.ammo << endl;
		inv.TotalCash -= 100;
		cout << "Total Cash: " << inv.TotalCash << endl;
		return true;
	}
	else
		return false;
}