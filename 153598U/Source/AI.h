#ifndef AI_H
#define AI_H
#include "Pathfinder.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Camera5.h"
class AI
{

public:
	AI();
	~AI();
	float getAngle();
	float gethandAngle(){ return handAngle; };
	void renderAlien(MS modelStack, unsigned int m_parameters, int material_enum);
	void move(Vector3 currentPos, Vector3 targetPos, Camera5 camera, Mesh ** meshList, int modelStart, int modelEnd, double time);
	void attack();
	Mesh * m_Head;
	Mesh * m_Body;
	Mesh * m_HandL;
	Mesh * m_HandR;
	Mesh * m_LegL;
	Mesh * m_LegR;
	float transparency;
private:
	Vector3 inBetween;
	int count;
	float handAngle;
	float angle;
	float prevAngle;
	Vector3 prevPos;
	PathFinding m_path;
};

#endif