#ifndef GUN_H_
#define GUN_H_

/**************************************************************************************************/
/*!
\file      Gun.h
\author   Jeffrey Low Zheng Long
\par
\brief
struct for the Guns
*/
/**************************************************************************************************/

struct Gun
{
public:
		/************************************************************************/
		/*!
		\brief a constructor for Guns and to initialise values
		*/
		/***********************************************************************/
		Gun(){ delayMultiplier = 0.3; semiAuto = false; reload = true; needAmmo = false; };
		/************************************************************************/
		/*!
		\brief The Destructor for Gun
		*/
		/***********************************************************************/
		~Gun(){};
		/************************************************************************/
		/*!
		\brief A boolean to turn on/off  Semi Automatic Firing
		\param
		*/
		/***********************************************************************/
		bool semiAuto;
		/************************************************************************/
		/*!
		\brief A boolean for Reloading
		\param
		*/
		/***********************************************************************/
		bool reload;
		/************************************************************************/
		/*!
		\brief A boolean for needing ammo
		*/
		/***********************************************************************/
		bool needAmmo;
		/************************************************************************/
		/*!
		\brief A float to add a gap in between bullet shot
		*/
		/***********************************************************************/
		float delayMultiplier;
		/************************************************************************/
		/*!
		\brief A boolean for stopping shooting
		*/
		/***********************************************************************/
		bool  stopFiring;
		/************************************************************************/
		/*!
		\brief A integer to count bullets in total
		*/
		/***********************************************************************/
		int ammo = 0;
		/************************************************************************/
		/*!
		\brief A integer to count bullets left in a clip.
		*/
		/***********************************************************************/
		int clip = 0;

};




#endif