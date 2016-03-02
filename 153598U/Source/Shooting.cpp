#include "Shooting.h"
#include "Enemy.h"
#include "Application.h"

Shooting::Shooting()
{
	bulletspeed = 100;
	delay = 0;
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
			Bullet temp;
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
			if (shooting == false)
			{
				flashTime = time + 0.02;
				shooting = true;
			}
			}
		}
	}
	if (time >= flashTime)
	{
		shooting = false;
	}
	if (Application::IsKeyPressed(VK_LBUTTON) && player.inv.GunSelected->semiAuto == true && shooting == false)
	{
	}
}

void Shooting::bulletHitDetection(vector<AI> &mobs, double dt, Camera5 camera)
{
	if (bullets.size() > 0)
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].Position.x += bullets[i].trajectory.Normalized().x * dt * bulletspeed;
			bullets[i].Position.y += bullets[i].trajectory.Normalized().y * dt * bulletspeed;
			bullets[i].Position.z += bullets[i].trajectory.Normalized().z * dt * bulletspeed;
		}
	}
	for (int i = 0; i < bullets.size(); ++i)
	{
		for (int j = 0; j < mobs.size(); ++j)
		{
			if (!mobs[j].isDead())
			{
				if (
					((bullets[i].Position.x > mobs[j].m_Head->min->x + mobs[j].position.x &&
					bullets[i].Position.y > mobs[j].m_Head->min->y + mobs[j].position.y &&
					bullets[i].Position.z > mobs[j].m_Head->min->z + mobs[j].position.z &&

					bullets[i].Position.x < mobs[j].m_Head->max->x + mobs[j].position.x &&
					bullets[i].Position.y < mobs[j].m_Head->max->y + mobs[j].position.y &&
					bullets[i].Position.z < mobs[j].m_Head->max->z + mobs[j].position.z) ||

					bullets[i].Position.x < mobs[j].m_Head->min->x + mobs[j].position.x &&
					bullets[i].Position.y < mobs[j].m_Head->min->y + mobs[j].position.y &&
					bullets[i].Position.z < mobs[j].m_Head->min->z + mobs[j].position.z &&

					(bullets[i].Position.x > mobs[j].m_Head->max->x + mobs[j].position.x &&
					bullets[i].Position.y > mobs[j].m_Head->max->y + mobs[j].position.y &&
					bullets[i].Position.z > mobs[j].m_Head->max->z + mobs[j].position.z))
					)
				{

					mobs[j].health -= 30;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
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
					mobs[j].health -= 15;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
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
					mobs[j].health -= 15;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
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
					mobs[j].health -= 15;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
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
					mobs[j].health -= 10;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
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
					mobs[j].health -= 10;
					if (mobs[j].health <= 0)
					{
						mobs[j].health = 0;
					}
					if (mobs[j].isDead())
					{
						mobs[j].deathAnimation(dt, camera);
						mobs[j].deathCount++;
					}
					bullets.erase(bullets.begin() + i);
					break;
				}
				else if (Vector3(bullets[i].Position - bullets[i].start).Length() >= 100)
				{
					bullets.erase(bullets.begin() + i);
					break;
				}
			}
		}
	}
}

