#include "Player.h"
#include  "Application.h"

void Player::currentItems(double dt, Camera5 camera, Mesh** meshList)
{
	time += dt;
	object = shop.ShopInteraction(dt, camera, meshList);
	if (Application::IsKeyPressed('X') && shop.openShop == false && inv.GunSelected== &inv.Rifle && inv.GunSelected->semiAuto == true && time > delay) //enable back Automatic fire
		//	glEnable(GL_CULL_FACE);
	{
		inv.GunSelected->delayMultiplier = 0.5;
		inv.GunSelected->semiAuto = false;
		delay = time + 0.5;
	}
	else  if (Application::IsKeyPressed('X') && shop.openShop == false && inv.GunSelected == &inv.Rifle && inv.GunSelected->semiAuto == false && time > delay) //disable back face cullinzgs
		//glDisable(GL_CULL_FACE);
	{
		inv.GunSelected->semiAuto = true;
		inv.GunSelected->delayMultiplier = 0.4;
		delay = time + 0.5;
	}
	if (Application::IsKeyPressed('E') && shop.openShop == false && time > delay&& object == meshList[SP2::GEO_STORE])
	{
		shop.openShop = true;
		cout << "shop is open bois";
		delay = time + 0.5;
	}
	else if (Application::IsKeyPressed('E') && shop.openShop == true && time > delay&& object == meshList[SP2::GEO_STORE])
	{
		shop.openShop = false;
		cout << "shop is close bois";
		delay = time + 0.5;
	}
	if (shop.openShop == true && object == meshList[SP2::GEO_STORE])
	{
		shop.shopping(inv,points);
	}
	if (Application::IsKeyPressed('1') && shop.openShop == false && time > delay)
	{
		inv.GunSelected = &inv.Rifle;
		delay = time + 0.5;
	}
	if (Application::IsKeyPressed('2') && shop.openShop == false && time > delay)
	{
		inv.GunSelected = &inv.SMG;
		delay = time + 0.5;
	}
	if (Application::IsKeyPressed('3') && shop.openShop == false && time > delay)
	{
		inv.GunSelected = &inv.Pistol;
		inv.GunSelected->semiAuto = true;
		delay = time + 0.5;
	}
}

float Player::getScaleHealth()
{
	 return Health / 100;
}

bool Player::isDead()
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}