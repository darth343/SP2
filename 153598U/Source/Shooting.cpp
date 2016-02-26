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
			//Vector3 tempRight = camera.right+camera.position;// Right Vector
			//Vector3   tempCameraPosition=(Vector3(camera.view+camera.position).Normalized() * 20)-tempRight;
			//temp.Position = camera.position;	
			temp.Position = camera.right + camera.position;
			if (player.inv.GunSelected == &player.inv.Rifle)
			{
				temp.Position.y -= 0.4;
				temp.Position.x +=0.3;
			}
			else if (player.inv.GunSelected==&player.inv.Pistol)
			{
				temp.Position.y -= 0.5;
				temp.Position.x -= 0.2;
			}
			else if (player.inv.GunSelected == &player.inv.SMG)
			{
				temp.Position.y -= 0.6;
				temp.Position.x += 0.1;
			}
			
			temp.start = camera.right + camera.position;
			temp.trajectory = Vector3(Vector3(camera.view * 500) - camera.right);
			bullets.push_back(temp);
			delay = time + player.inv.GunSelected->delayMultiplier;

			player.inv.GunSelected->ammo--;
			}

		}
	}
	if (Application::IsKeyPressed(VK_LBUTTON) && player.inv.GunSelected->semiAuto == true && player.inv.GunSelected->stopFiring == false/* && time>delay*/)
	{
		if (player.inv.GunSelected->semiAuto == true && player.inv.GunSelected->stopFiring == false)
		{

			if (player.inv.GunSelected->ammo > 0)
			{
				TestBullet temp;
				temp.Position = camera.right + camera.position;
			

				temp.Position = camera.right + camera.position;
				temp.start = camera.right + camera.position;
				if (player.inv.GunSelected == &player.inv.Rifle)
				{
					temp.Position.y -= 0.4;
					temp.Position.x += 0.3;
				}
				else if (player.inv.GunSelected == &player.inv.Pistol)
				{
					temp.Position.y -= 0.5;
					temp.Position.x -= 0.2;
				}
				else if (player.inv.GunSelected == &player.inv.SMG)
				{
					temp.Position.y -= 0.6;
					temp.Position.x += 0.1;
				}
				temp.trajectory = Vector3(Vector3(camera.view * 500) - camera.right);
				bullets.push_back(temp);
				delay = time + player.inv.GunSelected->delayMultiplier;

				player.inv.GunSelected->ammo--;
				player.inv.GunSelected->stopFiring = true;
			}
			//
			//temp.Position = camera.position;
			//temp.start = temp.Position;
			//temp.trajectory = camera.view.Normalized();
			//bullets.push_back(temp);
			//delay = time + player.inv.GunSelected->delayMultiplier;
			//player.inv.GunSelected->ammo -= 1;
			//	std::cout << player.inv.GunSelected->ammo << std::endl;
			
			
			
			}
		
	}
	else if (!Application::IsKeyPressed(VK_LBUTTON))
	{
	player.inv.GunSelected->stopFiring = false;
	}
	//if (bullets.size() > 0 )//&& GunFiring==true)
	//{
	//	for (int i = 0; i < bullets.size(); i++)
	//	{
	//		bullets[i].Position.x += bullets[i].trajectory.Normalized().x * bulletspeed;
	//		bullets[i].Position.y += bullets[i].trajectory.Normalized().y * bulletspeed;
	//		bullets[i].Position.z += bullets[i].trajectory.Normalized().z * bulletspeed;
	//	}
	//}
	/*else*/ if (bullets.size() > 0)// && JetFiring == true)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Position.x += bullets[i].trajectory.Normalized().x * dt * bulletspeed;
			bullets[i].Position.y += bullets[i].trajectory.Normalized().y * dt * bulletspeed;
			bullets[i].Position.z += bullets[i].trajectory.Normalized().z * dt * bulletspeed;
		}
	}
}

void Shooting::bulletHitDetection(vector<AI> &mobs, double dt, Camera5 camera)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		for (int j = 0; j < mobs.size(); ++j)
		{
			if (
				(bullets[i].Position.x > mobs[j].m_Head->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_Head->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_Head->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_Head->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_Head->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_Head->max->z + mobs[j].position.z ) ||

				bullets[i].Position.x < mobs[j].m_Head->min->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_Head->min->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_Head->min->z + mobs[j].position.z &&

				(bullets[i].Position.x > mobs[j].m_Head->max->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_Head->max->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_Head->max->z + mobs[j].position.z)
				//((bullets[i].Position.x > mobs[j].m_Head->max->x + mobs[j].position.x && bullets[i].Position.x < mobs[j].m_Head->min->x + mobs[j].position.x) ||
				//(bullets[i].Position.x < mobs[j].m_Head->max->x + mobs[j].position.x && bullets[i].Position.x < mobs[j].m_Head->min->x + mobs[j].position.x)) &&

				////((bullets[i].Position.y > mobs[j].m_Head->max->y + mobs[j].position.y && bullets[i].Position.y < mobs[j].m_Head->min->y + mobs[j].position.y) ||
				////(bullets[i].Position.y < mobs[j].m_Head->max->y + mobs[j].position.y && bullets[i].Position.y < mobs[j].m_Head->min->y + mobs[j].position.y)) &&


				//((bullets[i].Position.z > mobs[j].m_Head->max->z + mobs[j].position.z && bullets[i].Position.z < mobs[j].m_Head->min->z + mobs[j].position.z) ||
				//(bullets[i].Position.z < mobs[j].m_Head->max->z + mobs[j].position.z && bullets[i].Position.z < mobs[j].m_Head->min->z + mobs[j].position.z))
				)
			{
				cout << "HEADSHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (
				bullets[i].Position.x > mobs[j].m_Body->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_Body->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_Body->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_Body->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_Body->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_Body->max->z + mobs[j].position.z
				)
			{
				cout << "BODYSHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (
				bullets[i].Position.x > mobs[j].m_HandR->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_HandR->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_HandR->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_HandR->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_HandR->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_HandR->max->z + mobs[j].position.z
				)
			{
				cout << "RIGHT HAND SHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (
				bullets[i].Position.x > mobs[j].m_HandL->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_HandL->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_HandL->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_HandL->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_HandL->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_HandL->max->z + mobs[j].position.z
				)
			{
				cout << "LEFT HAND SHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (
				bullets[i].Position.x > mobs[j].m_LegL->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_LegL->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_LegL->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_LegL->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_LegL->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_LegL->max->z + mobs[j].position.z
				)
			{
				cout << "LEFT LEG SHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (
				bullets[i].Position.x > mobs[j].m_LegR->min->x + mobs[j].position.x &&
				bullets[i].Position.y > mobs[j].m_LegR->min->y + mobs[j].position.y &&
				bullets[i].Position.z > mobs[j].m_LegR->min->z + mobs[j].position.z &&

				bullets[i].Position.x < mobs[j].m_LegR->max->x + mobs[j].position.x &&
				bullets[i].Position.y < mobs[j].m_LegR->max->y + mobs[j].position.y &&
				bullets[i].Position.z < mobs[j].m_LegR->max->z + mobs[j].position.z
				)
			{
				cout << "RIGHT LEG SHOT" << j << endl;
				bullets.erase(bullets.begin() + i);
				break;
			}
			else if (Vector3(bullets[i].Position - bullets[i].start).Length() >= 100)
			{
				bullets.erase(bullets.begin() + i);
				//return nullptr;
				break;
			}
			//cout << bullets[i].Position << endl;
		}
		//for (int i = 0; i < mobs.size(); i++)
		//{
			//if (mobs[i].enemyMesh->min != nullptr || mobs[i].enemyMesh->max != nullptr){

			//	int offset = 1;
			//	if ((bullets[a].Position.x >mobs[i].enemyMesh->min->x + mobs[i].enemyMesh->position.x - offset && bullets[a].Position.x < mobs[i].enemyMesh->max->x + mobs[i].enemyMesh->position.x + offset) &&
			//		(bullets[a].Position.y >mobs[i].enemyMesh->min->y + mobs[i].enemyMesh->position.y - offset&& bullets[a].Position.y < mobs[i].enemyMesh->max->y + mobs[i].enemyMesh->position.y + offset) &&
			//		(bullets[a].Position.z >mobs[i].enemyMesh->min->z + mobs[i].enemyMesh->position.z - offset&& bullets[a].Position.z < mobs[i].enemyMesh->max->z + mobs[i].enemyMesh->position.z + offset)
			//		)
			//	{
			//		if (damage.headShot==true)
			//		{
			//			damage.damageMultiplier = 2.5;
			//		}
			//		else if (damage.normalShot == true)
			//		{
			//			damage.damageMultiplier = 1;
			//		}
			//		else if (damage.legShot == true)
			//		{
			//			damage.damageMultiplier = 0.5;
			//		}
			//		mobs[i].enemyMesh->health -= 10*damage.damageMultiplier;
			//		if (mobs[i].enemyMesh->health <= 0)
			//		{
			//			 mobs[i].enemyMesh->ifShootable = false;
			//			mobs[i].enemyMesh->health = 0;
			//			
			//		}

			//		bullets.erase(bullets.begin() + a);
			//		//return mobs[i].enemyMesh;
			//		break;
			//	}
			//	else
			//	{
			//		cout << "Test" << endl;
				//}


			//}
		//}
	}
}

