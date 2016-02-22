#include "Shooting.h"
#include "Application.h"

//#include "SP2.h"
//#include "timer.h"

Shooting::Shooting()
{
	objectDied = false;
	shot = false;
}
Shooting::~Shooting()
{

}

void Shooting::ShootingBullets(Camera5 camera,double dt,float time,Mesh** meshList)
{
	
	if (Application::IsKeyPressed(VK_LBUTTON) && time > delay)
	{
		TestBullet temp;
		temp.Position = camera.position;
		temp.start = temp.Position;
		temp.trajectory = camera.view.Normalized();
		bullets.push_back(temp);
		delay = time + 0.1;
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
	// check if bullet position is
	// in any mesh ( check position with mesh min and max value )
	// if in any mesh, check if mesh is shootable
	// if mesh is shootable
	// minus health from mesh
	// erase bullet from vector
	// else if its not in object
	// check if vector length is above range
	// if above range, erase bullet from vector
// 	object = Shootable(dt, camera, meshList); 
	if (bullets.size() > 0)
	{
		for (int a = 0; a < bullets.size(); a++)
		{
			for (int i = 0; i < mobs.size(); i++)
			{
				if (mobs[i].EnemyMesh->min != nullptr || mobs[i].EnemyMesh->max != nullptr){

					int offset = 0.5;
					if ((bullets[a].Position.x >mobs[i].EnemyMesh->min->x + mobs[i].EnemyMesh->position.x - offset && bullets[a].Position.x < mobs[i].EnemyMesh->max->x + mobs[i].EnemyMesh->position.x + offset) &&
						(bullets[a].Position.y >mobs[i].EnemyMesh->min->y + mobs[i].EnemyMesh->position.y - offset&& bullets[a].Position.y < mobs[i].EnemyMesh->max->y + mobs[i].EnemyMesh->position.y + offset) &&
						(bullets[a].Position.z >mobs[i].EnemyMesh->min->z + mobs[i].EnemyMesh->position.z - offset&& bullets[a].Position.z < mobs[i].EnemyMesh->max->z + mobs[i].EnemyMesh->position.z + offset)
						)
					{
						mobs[i].health -= 10;
						bullets.erase(bullets.begin() + a);
						break;
					}
					else
					{
						if (Vector3(bullets[a].Position - bullets[a].start).Length() >= 500)
						{
							bullets.erase(bullets.begin() + a);
							break;
						}
					}


				}
			}
		}
	}


}

//MESH*
//HEALTH
//ENEMY
//STRUCT
//VEECTOR OF ENEMY STRUCT, ALL MOBS
//PUSH IN A CUBE
