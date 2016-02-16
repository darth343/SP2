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
using std::map;
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
	map	<Mesh*, int> objectHealth;
	string timeDisplay="Time : ";
	float time = 0;
	float delay = 0;
	int fuel = 100;
	//string timeString;
	string jetfuelDisplay = "Jet Fuel: ";
	bool shot=false ; // when object get shot
	bool objectDied = false;//when object is dead
};

#endif