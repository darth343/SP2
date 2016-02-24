#ifndef PATH_TEST_H
#define PATH_TEST_H

#include "Scene.h"
#include "Camera5.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Enemy.h"
#include "Pathfinder.h"
#include "FlyingClass.h"
#include "Vector3.h"
using std::vector;
using std::string;
class Test : public Scene
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
		GEO_FUEL1,
		GEO_FUEL2,
		GEO_FUEL3,
		GEO_FUEL4,
		GEO_FUEL5,
		GEO_BLOCK,
		GEO_ALIEN_HEAD,
		GEO_ALIEN_HANDR,
		GEO_ALIEN_HANDL,
		GEO_ALIEN_BODY,
		GEO_ALIEN_LEGR,
		GEO_ALIEN_LEGL,
		GEO_MODEL1,
		GEO_TEXT,
		GEO_PATH_F,
		GEO_PATH_V,
		GEO_PATH_O,

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
	Test();
	~Test();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	//Mesh* Shootable(double dt);
	Mesh* meshList[NUM_GEOMETRY];
	PathFinding path;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox(Vector3 position);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y);
	void CharacMovement(double dt);
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	unsigned m_vertexArrayID;

	float gravity = 10;
	float rotateAngle;
	float fps;
	float trans;
	MS modelStack, viewStack, projectionStack;
	Light light[4];
	Camera5 camera;
	string timeDisplay = "Time : ";
	float time = 0;
	float delay = 0;
	string jetfuelDisplay = "Jet Fuel: ";
	Flying jetPack;
	Vector3 temp1;
	float angle;
	float prevAngle;
	bool animate = false;
};

#endif