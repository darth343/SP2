#ifndef SP2_H
#define SP2_H

#include "Scene.h"
#include "Camera4.h"
#include "Camera5.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "timer.h"
#include "Shooting.h"
#include "Enemy.h"
#include "Pathfinder.h"
#include "Movement.h"
#include <Vector>
#include "FlyingClass.h"
#include "AI.h"
#include "Gun.h"
#include "Shop.h"
#include "Player.h"

using std::vector;
using std::string;
class SP2 : public Scene
{
public:
	static enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_FRONT,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_BACK,
		GEO_TIMEDISPLAY,
		GEO_TIME,
		GEO_FUEL1,
		GEO_FUEL2,
		GEO_FUEL3,
		GEO_FUEL4,
		GEO_FUEL5,
		GEO_JETPACKUI,
		GEO_UIBG,
		GEO_GUNMODE,
		GEO_PLAYERHEALTH,
		GEO_ENEMYHEALTH,
		GEO_ENEMYHEALTHDISPLAY,
		GEO_BULLET,
		GEO_ALIEN_HEAD,
		GEO_ALIEN_HANDR,
		GEO_ALIEN_HANDL,
		GEO_ALIEN_BODY,
		GEO_ALIEN_LEGR,
		GEO_ALIEN_LEGL,
		GEO_HELMET,
		GEO_CROSSHAIR,
		GEO_MODEL1,

		//Turrets
		GEO_TURRET1,
		//TurretsEnd

		//// New Arena Stuff
		//GEO_1STMAZEWALL1,
		//GEO_1STMAZEWALL2,
		//GEO_1STMAZEWALL3,
		//GEO_1STMAZEWALL4,
		//GEO_1STMAZEWALL5,
		//GEO_1STMAZEWALL6,
		//GEO_1STMAZEWALL7,

		/*

		



	,*/

		////Walls
		GEO_LONGWALL,
		GEO_FLOOR1,
		GEO_FLOOR2,
		GEO_CRATES1,
		GEO_CRATES2,
		GEO_CRATES3,
		GEO_BALANCE1,
		GEO_BALANCE2,
		GEO_BALANCE3,
		GEO_FLOOR3,
		GEO_WALLRUN1,
		GEO_WALLRUN2,
		GEO_WALLRUN3,
		GEO_WALLRUN4,
		GEO_WALLRUN5,
		GEO_WALLRUN6,
		GEO_FLOOR4,
		GEO_TALLWALL1,
		GEO_TALLWALL2,
		GEO_TALLWALL3,
		GEO_TALLCRATE,
		GEO_FLOOR5,
		GEO_FLOOR6,
		GEO_FLOOR7,
		GEO_FLOOR8,
		GEO_WALLWALL1,
		GEO_WALLWALL2,
	
		GEO_ARENAFRONTWALL1,
		GEO_ARENAFRONTWALL2,
		GEO_ARENAFRONTWALL3,
		GEO_ARENALEFTWALL,
		GEO_ARENARIGHTWALL,
		GEO_ARENABACKWALL1,
		GEO_ARENABACKWALL2,
		GEO_ARENABACKWALL3,
		GEO_LANDINGPAD1,
		GEO_LANDINGPAD2,

		GEO_BACKINTERSECTWALL,
		GEO_FRONTINTERSECTWALL,
		GEO_LEFTINTERSECTWALL,
		GEO_RIGHTINTERSECTWALL,

		GEO_MIDDLEPILLAR,
		
		// New Arena Stuff
		GEO_1STMAZEWALL1,
		GEO_1STMAZEWALL2,
		GEO_1STMAZEWALL3,
		GEO_1STMAZEWALL4,
		GEO_1STMAZEWALL5,
		GEO_1STMAZEWALL6,
		GEO_1STMAZEWALL7,
		

		GEO_2NDMAZEWALL1,
		GEO_2NDMAZEWALL2,
		GEO_2NDMAZEWALL3,
		GEO_2NDMAZEWALL4,
		GEO_2NDMAZEWALL5,
		GEO_2NDMAZEWALL6,

		GEO_3RDMAZEWALL1,
		GEO_3RDMAZEWALL2,
		GEO_3RDMAZEWALL3,
		GEO_3RDMAZEWALL4,
		GEO_3RDMAZEWALL5,
		GEO_3RDMAZEWALL6,
		GEO_3RDMAZEWALL7,
		GEO_3RDMAZEWALL8,
		

		GEO_4THMAZEWALL1,
		GEO_4THMAZEWALL2,
		GEO_4THMAZEWALL3,
		GEO_4THMAZEWALL4,
		GEO_4THMAZEWALL5,
		GEO_4THMAZEWALL6,
		GEO_4THMAZEWALL7,
		GEO_4THMAZEWALL8,

		GEO_DOOR,

		GEO_GROUND,

		//Arena
	/*	GEO_ARENAWALLFRONT,
		GEO_ARENAWALLBACK,
		GEO_ARENAWALLLEFT,
		GEO_ARENAWALLRIGHT,
		GEO_BARREL1,
		GEO_BARREL2,
		GEO_BARREL3,
		GEO_BARREL4,
		GEO_CRATE1,
		GEO_CRATE2,
		GEO_CRATE3,
		GEO_CRATE4,
		GEO_SQPYRA1,
		GEO_SQPYRA2,
		GEO_RDPYRA1,*/
	//	GEO_RDPYRA2,
		//ArenaEnd

		GEO_TEXT,
		GEO_RIFLE,
		GEO_ENEMY,
		GEO_FLASH,
		GEO_PATH_F,
		GEO_PATH_V,
		GEO_PATH_O,
		GEO_STORE,
		GEO_PISTOL,
		GEO_SMG,
		NUM_GEOMETRY,
	};
static enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_MATERIAL_TRANSPARENCY,

		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,

		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_NUMLIGHTS,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,


		U_TOTAL,
	};
	SP2();
	~SP2();
	void Scenario3Init();
	void Scenario2Init();
	void Scenario3Render();
	void Scenario2Render();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	Mesh* meshList[NUM_GEOMETRY];
	Shooting shoot;
	void RenderMesh(Mesh *mesh, bool enableLight);
	static void RenderMesh(Mesh *mesh, bool enableLight, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	static void RenderText(Mesh* mesh, std::string text, Color color, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	void RenderSkybox(Vector3 position);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y);
	Mesh* Interaction(double dt);

	private:
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;
	
	float gravity = 10;
	float rotateAngle;
	float fps;
	float scaleHealth = 1;
	MS modelStack, viewStack, projectionStack;
	Light light[4];

	Movement move;

	vector<enemy> mobs;
	Camera5 camera;
	string timeDisplay="Time : ";
	float time = 0;
	float delay = 0;
	bool shot=false ; // when object get shot
	bool objectDied = false;//when object is dead
	bool takeDamage = false;
	//AI alien;
	vector<AI> allAliens;
	Mesh* object;
	Shop shop;
	Player player;
	Vector3 pivot;
//	Mesh* object;


	bool surviveDone=false;
};

#endif