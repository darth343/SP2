/******************************************************************************/
/*!
\file	Coins.h
\author Tay Kiat Yeow
\par	email: epicfantasygamers@gmail.com
\brief
Header file for all coin related functions and definations
*/
/******************************************************************************/
#ifndef COINS_H
#define COINS_H
#include <vector>
#include "Player.h"
#include "Mesh.h"
#include "Camera5.h"
/******************************************************************************/
/*!
Class coins:
\brief	coins class
*/
/******************************************************************************/
class coins
{
public:
	coins(){};
	~coins(){};
	std::vector<Mesh *> allCoins;
	/******************************************************************************/
	/*!
	inits all coin positions
	*/
	/******************************************************************************/
	void init();
	/******************************************************************************/
	/*!
	function for picking up coins
	*/
	/******************************************************************************/
	void pickup(Camera5 camera, Player & player);
	int acquired = 0;
	float rotateAngle = 0;
};
#endif