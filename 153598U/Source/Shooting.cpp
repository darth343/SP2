#include "Shooting.h"
#include "Enemy.h"
#include "Application.h"

//#include "SP2.h"
//#include "timer.h"

Shooting::Shooting()
{
	objectDied = false;
	//shot = false;
}
Shooting::~Shooting()
{

}

void Shooting::ShootingBullets(Camera5 camera,double dt,float time,Mesh** meshList,Player &player )
{
	if (Application::IsKeyPressed(VK_LBUTTON) && player.inv.GunSelected->semiAuto == false)
	{
		if (player.inv.GunSelected->semiAuto == false && time > delay)
		{
			if (player.inv.GunSelected->ammo > 0)
			{
			TestBullet temp;
			temp.Position = camera.position;
			temp.start = temp.Position;
			temp.trajectory = camera.view.Normalized();
			bullets.push_back(temp);
			delay = time + player.inv.GunSelected->delayMultiplier;
				player.inv.GunSelected->ammo--;
				std::cout << player.inv.GunSelected->ammo << std::endl;
			}

		}
	}
	if (Application::IsKeyPressed(VK_LBUTTON) && player.inv.GunSelected->semiAuto == true && player.inv.GunSelected->stopFiring == false/* && time>delay*/)
	{
		if (player.inv.GunSelected->semiAuto == true && player.inv.GunSelected->stopFiring == false)
		{
			if (player.inv.GunSelected->ammo > 0)
			{
			cout << " Works" << endl;
			TestBullet temp;
			temp.Position = camera.position;
			temp.start = temp.Position;
			temp.trajectory = camera.view.Normalized();
			bullets.push_back(temp);
			delay = time + player.inv.GunSelected->delayMultiplier;
			player.inv.GunSelected->ammo -= 1;
				std::cout << player.inv.GunSelected->ammo << std::endl;
			player.inv.GunSelected->stopFiring = true;
			
			
			}
		}
	}
	else if (!Application::IsKeyPressed(VK_LBUTTON))
	{
	player.inv.GunSelected->stopFiring = false;
	}
	if (bullets.size() > 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Position.x += bullets[i].trajectory.Normalized().x * bulletspeed;
			bullets[i].Position.y += bullets[i].trajectory.Normalized().y * bulletspeed;
			bullets[i].Position.z += bullets[i].trajectory.Normalized().z * bulletspeed;
		}
	}
}

void Shooting::bulletHitDetection(vector<enemy> &mobs, double dt, Camera5 camera)
{
	
	if (bullets.size() > 0)
	{
		for (int a = 0; a < bullets.size(); a++)
		{
			for (int i = 0; i < mobs.size(); i++)
			{
				if (mobs[i].enemyMesh->min != nullptr || mobs[i].enemyMesh->max != nullptr){

					int offset = 1;
					if ((bullets[a].Position.x >mobs[i].enemyMesh->min->x + mobs[i].enemyMesh->position.x - offset && bullets[a].Position.x < mobs[i].enemyMesh->max->x + mobs[i].enemyMesh->position.x + offset) &&
						(bullets[a].Position.y >mobs[i].enemyMesh->min->y + mobs[i].enemyMesh->position.y - offset&& bullets[a].Position.y < mobs[i].enemyMesh->max->y + mobs[i].enemyMesh->position.y + offset) &&
						(bullets[a].Position.z >mobs[i].enemyMesh->min->z + mobs[i].enemyMesh->position.z - offset&& bullets[a].Position.z < mobs[i].enemyMesh->max->z + mobs[i].enemyMesh->position.z + offset)
						)
					{
						if (damage.headShot==true)
						{
							damage.damageMultiplier = 2.5;
						}
						else if (damage.normalShot == true)
						{
							damage.damageMultiplier = 1;
						}
						else if (damage.legShot == true)
						{
							damage.damageMultiplier = 0.5;
						}
						mobs[i].enemyMesh->health -= 10*damage.damageMultiplier;
						if (mobs[i].enemyMesh->health <= 0)
						{
							 mobs[i].enemyMesh->ifShootable = false;
							mobs[i].enemyMesh->health = 0;
							
						}

						bullets.erase(bullets.begin() + a);
						//return mobs[i].enemyMesh;
						break;
					}
					else
					{
						if (Vector3(bullets[a].Position - bullets[a].start).Length() >= 500)
						{
							bullets.erase(bullets.begin() + a);
							//return nullptr;
							break;
						}
					}


				}
			}
		}
	}


}
Mesh* Shooting::Shootable(double dt, Camera5 camera, Mesh** meshList, vector<enemy> &mobs)
{
	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range; temp += camera.view.Normalized())
	{
		
		for (int i = 0; i < mobs.size(); i++)
		{
			if (mobs[i].enemyMesh->min != nullptr || mobs[i].enemyMesh->max != nullptr)
		{
				if ((temp.x + camera.position.x <= mobs[i].enemyMesh->max->x + mobs[i].enemyMesh->position.x + offset && temp.x + camera.position.x >= mobs[i].enemyMesh->min->x + mobs[i].enemyMesh->position.x - offset) //Check min and max for x
					&& (temp.y + camera.position.y <= mobs[i].enemyMesh->max->y + mobs[i].enemyMesh->position.y + offset && temp.y + camera.position.y >= mobs[i].enemyMesh->min->y + mobs[i].enemyMesh->position.y - offset) //Check min and max for y
					&& (temp.z + camera.position.z <= mobs[i].enemyMesh->max->z + mobs[i].enemyMesh->position.z + offset && temp.z + camera.position.z >= mobs[i].enemyMesh->min->z + mobs[i].enemyMesh->position.z - offset)) //Check min and max for z
				{		
					if (mobs[i].enemyMesh->ifShootable == false)
					{
						return nullptr;
						break;
					}
					else
					{
						mobs[i].enemyMesh->ifShootable = true;
						return mobs[i].enemyMesh;
						break;
					}
				}
			}
		}
	}
	return nullptr;
}

