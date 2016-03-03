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
#include "Pathfinder.h"
#include "Movement.h"
#include <Vector>
#include "FlyingClass.h"
#include "AI.h"
#include "Gun.h"
#include "Shop.h"
#include "Player.h"
#include "TriggerBox.h"
#include "Coins.h"
#include "Scenario2Subs.h"

using std::vector;
using std::string;

struct button
{
	Vector3 mini;
	Vector3 maxi;
};

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
		GEO_MAINMENU,
		GEO_MAINMENUBOX1,
		GEO_MAINMENUBOX2,

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
		GEO_STORE,
		GEO_DOOR,

		GEO_GROUND,

		//Runner
		GEO_RAINBOW,
		GEO_ROCK1,
		GEO_ROCK2,
		GEO_ROCK3,
		GEO_ROCK4,
		GEO_ROCK5,
		GEO_ROCK6,
		GEO_ROCK7,
		GEO_ROCK8,
		GEO_ROCK9,
		GEO_ROCK10,
		GEO_ROCK11,
		GEO_ROCK12,
		GEO_ROCK13,
		GEO_ROCK14,
		GEO_ROCK15,
		GEO_ROCK16,
		GEO_ROCK17,
		GEO_ROCK18,
		GEO_ROCK19,
		GEO_ROCK20,
		GEO_ROCK21,
		GEO_ROCK22,
		GEO_ROCK23,
		GEO_ROCK24,
		GEO_ROCK25,
		GEO_ROCK26,
		GEO_ROCK27,
		GEO_ROCK28,
		GEO_ROCK29,
		GEO_ROCK30,
		GEO_ROCK31,
		GEO_ROCK32,
		GEO_ROCK33,
		GEO_ROCK34,
		GEO_ROCK35,
		GEO_ROCK36,
		GEO_ROCK37,
		GEO_ROCK38,
		//RunnerEnd
		GEO_TEXT,
		GEO_RIFLE,
		GEO_ENEMY,
		GEO_FLASH,
		GEO_PATH_F,
		GEO_PATH_V,
		GEO_PATH_O,
		GEO_PISTOL,
		GEO_SMG,
		GEO_SHOPMENU,
		GEO_BLACKSCREEN, 
		GEO_RUNNERSCREEN,
		GEO_GAMEOVER,
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
enum gameState
{
	MAIN_MENU,
	SCENARIO1,
	TRANSITION1,
	SCENARIO2,
	TRANSITION2,
	SCENARIO3,
	ENDING,
	DISABLE_MOUSE,
};
	SP2();
	~SP2();
	void ScenarioParkourInit();
	void ScenarioArenaInit();
	void ScenarioRunnerInit();
	void ScenarioParkourRender();
	void ScenarioArenaRender();
	void ScenarioRunnerRender();
	void PlayerPoints();
	void RenderCoins();
	void RenderUI();
	void RenderShop();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	Mesh* meshList[NUM_GEOMETRY];
	Shooting shoot;
	void RenderMesh(Mesh *mesh, bool enableLight);
	static void RenderMesh(Mesh *mesh, bool enableLight, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	static void RenderText(Mesh* mesh, std::string text, Color color, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	static void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	static void RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL]);
	void RenderSkybox(Vector3 position);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y);
	void ButtonPress(double mouseX, double mouseY);
	Mesh* Interaction(double dt);
	Color colorRun(Vector3 position);

	private:
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;
	
	float gravity = 10;
	float rotateAngle;
	float fps;
	MS modelStack, viewStack, projectionStack;
	Light light[4];
	Movement move;
	Camera5 camera;
	string timeDisplay="Time : ";
	Scenario2_Subtitles subs;
	float time = 0;
	float delay = 0;
	//int points = 50;
	bool shot=false ; // when object get shot
	bool objectDied = false;//when object is dead
	bool takeDamage = false;

	//Coins
	coins coin;
	gameState state;
	button Start;
	button Quit;
	//AI alien;
	vector<AI> allAliens;
	Shop shop;
	Player player;
	Vector3 pivot;
	vector<TriggerBox> events;

	bool surviveDone=false;
};

#endif