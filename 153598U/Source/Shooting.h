#ifndef SHOOTING_H_
#define SHOOTING_H_
#include <vector>
#include"Camera5.h"
#include "Mesh.h"
#include "Vector3.h"
#include "AI.h"
#include <iostream>
#include "Gun.h"
#include "Damage.h"
#include "Player.h"
using std::cout;
using std::endl;
using std::vector;

/**************************************************************************************************/
/*!
\file     Shooting.h
\author   Jeffrey Low Zheng Long
\par
\brief
class for Shooting stuff
*/
/**************************************************************************************************/
class Shooting 
{
public:
	/************************************************************************/
	/*!
	\brief A struct that defines Bullet properties
	*/
	/***********************************************************************/
	struct Bullet
	{
		Vector3 Position;
		Vector3 start;
		Vector3 trajectory;
	};
	/************************************************************************/
	/*!
	\brief A constructor for Shooting
	*/
	/***********************************************************************/
	Shooting();
	/************************************************************************/
	/*!
	\brief A destructor for Shooting
	*/
	/***********************************************************************/
	~Shooting();
	/************************************************************************/
	/*!
	\brief A function that shoots Bullets 
	\param takes in delta time,camera stuff , the time ,the mesh list and a reference to player
	*/
	/***********************************************************************/
	void ShootingBullets(Camera5 camera, double dt, float time,Mesh** meshList, Player &player);
	/************************************************************************/
	/*!
	\brief A function that checks whether the bullet has hit an enemy
	\param takes in a vector of AI, delta time and camera
	*/
	/***********************************************************************/
	void bulletHitDetection(vector<AI> &mobs, double dt, Camera5 camera);
	/************************************************************************/
	/*!
	\brief A function to reload the gun
	\param  takes in a reference to player, delta time and current game time
	*/
	/***********************************************************************/
	void reloadClip(Player &player, double dt,float time);
	/************************************************************************/
	/*!
	\brief A vector of a Bullet Struct
	*/
	/***********************************************************************/
	vector<Bullet> bullets;
	/************************************************************************/
	/*!
	\brief A float for how fast bullet travel
	*/
	/***********************************************************************/
	float bulletspeed;
	/************************************************************************/
	/*!
	\brief A float for a delay between function
	*/
	/***********************************************************************/
	float delay;
	/************************************************************************/
	/*!
	\brief  A boolean for shooting
	*/
	/***********************************************************************/
	bool shooting = false;
	/************************************************************************/
	/*!
	\brief  A float for how long the flash last
	*/
	/***********************************************************************/
	float flashTime = 0;
	//bool GunFiring;
	//bool JetFiring;
};




#endif