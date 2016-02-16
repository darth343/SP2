#ifndef SP2_H
#define SP2_H

#include "Scene.h"
#include "Camera4.h"
#include "Camera5.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "timer.h"
#include <map>
#include <Vector>
using std::vector;
using std::string;
class SP2 : public Scene
{
	struct TestBullet
	{
		Vector3 Position;
		Vector3 start;
		Vector3 trajectory;
		Mesh * object;
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_FRONT,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_BACK,
		GEO_GROUND,
		GEO_TIMEDISPLAY,
		GEO_TIME,
		GEO_FUEL1,
		GEO_FUEL2,
		GEO_FUEL3,
		GEO_FUEL4,
		GEO_FUEL5,
		GEO_JETPACKUI,
		GEO_ENEMYHEALTH,
		GEO_ENEMYHEALTHDISPLAY,
		GEO_BULLET,
		GEO_MODEL1,
		//GEO_SP2_MODELBLOCK,
		//GEO_SP2_MODELWALLTHIN,
		//GEO_SP2_MODELWALLTHICK,
		GEO_STARTLINE,

		//Walls
		GEO_LEFTWALL1,
		GEO_RIGHTWALL1,
		GEO_LEFTWALL2,
		GEO_RIGHTWALL2,
		GEO_LEFTWALL3,
		GEO_RIGHTWALL3,
		GEO_LEFTWALL4,
		GEO_RIGHTWALL4,
		GEO_LEFTWALL5,
		GEO_RIGHTWALL5,
		GEO_LEFTWALL6,
		GEO_RIGHTWALL6,
		GEO_LEFTWALL7,
		GEO_RIGHTWALL7,
		GEO_LEFTWALL8,
		GEO_RIGHTWALL8,
		GEO_LEFTWALL9,
		GEO_RIGHTWALL9,
		GEO_LEFTWALL10,
		GEO_RIGHTWALL10,
		GEO_LEFTWALL11,
		GEO_RIGHTWALL11,
		GEO_LEFTWALL12,
		GEO_RIGHTWALL12,
		GEO_LEFTWALL13,
		GEO_RIGHTWALL13,
		GEO_LEFTWALL14,
		GEO_RIGHTWALL14,
		GEO_LEFTWALL15,
		GEO_RIGHTWALL15,
		GEO_LEFTWALL16,
		GEO_RIGHTWALL16,
		GEO_LEFTWALL17,
		GEO_RIGHTWALL17,
		GEO_LEFTWALL18,
		GEO_RIGHTWALL18,
		GEO_LEFTWALL19,
		GEO_RIGHTWALL19,
		GEO_LEFTWALL20,
		GEO_RIGHTWALL20,
		GEO_LEFTWALL21,
		GEO_RIGHTWALL21,
		GEO_LEFTWALL22,
		GEO_RIGHTWALL22,
		GEO_LEFTWALL23,
		GEO_RIGHTWALL23,
		GEO_LEFTWALL24,
		GEO_RIGHTWALL24,
		GEO_LEFTWALL25,
		GEO_RIGHTWALL25,
		GEO_LEFTWALL26,
		GEO_RIGHTWALL26,
		GEO_LEFTWALL27,
		GEO_RIGHTWALL27,
		GEO_LEFTWALL28,
		GEO_RIGHTWALL28,
		GEO_LEFTWALL29,
		GEO_RIGHTWALL29,
		//WallEnd

		//Blocks
		GEO_BLOCK1,
		GEO_BLOCK2,
		GEO_BLOCK3,
		GEO_BLOCK4,
		GEO_BLOCK5,
		GEO_BLOCK6,
		GEO_BLOCK7,
		GEO_BLOCK8,
		GEO_BLOCK9,
		GEO_BLOCK10,
		//BlocksEnd

		//Wall(Thin)
		GEO_THIN1,
		GEO_THIN2,
		GEO_THIN3,
		//Wall(Thin)End

		//Wall(Thin)2
		GEO_THINz1,
		GEO_THINz2,
		GEO_THINz3,
		GEO_THINz4,
		GEO_THINz5,
		GEO_THINz6,
		GEO_THINz7,
		GEO_THINz8,
		GEO_THINz9,
		//Wall(Thin)2End

		//Wall(Thick)
		GEO_THICK1,
		GEO_THICK2,
		//Wall(Thick)End
		GEO_TEXT,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
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
public:
	SP2();
	~SP2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(Vector3 position);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y);
	void Movement(double dt);
	void CharacMovement(double dt);
	Mesh* Interaction(double dt);
	Mesh* Shooting(double dt);

	unsigned m_vertexArrayID;
	Mesh*  meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	int amtBullet=0;
	TestBullet temp;
	TestBullet tempMag;
	vector<TestBullet> bullets;
	float gravity = 10;
	float rotateAngle;
	float fps;
	Camera5 camera;
	MS modelStack, viewStack, projectionStack;
	Light light[4];
	Mesh * object;
	float trans = 0;
	int healthPoints=100;
	vector<int> Health;
	vector<int> objectIDAll;
	string timeDisplay="Time : ";
	float time = 0;
	float delay = 0;
	int fuel = 100;
	string jetfuelDisplay = "Jet Fuel: ";
	bool shot=false ; // when object get shot
	bool objectDied = false;//when object is dead
};

#endif