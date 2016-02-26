#ifndef AI_H
#define AI_H
#include "Pathfinder.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Camera5.h"
#include <vector>

class AI
{

public:
	AI()
	{
		allMesh.push_back(m_Head);
		allMesh.push_back(m_Body);
		allMesh.push_back(m_HandL);
		allMesh.push_back(m_HandR);
		allMesh.push_back(m_LegL);
		allMesh.push_back(m_LegR);
		m_Head	= 0;
		m_Body	= 0;
		m_HandL	= 0;
		m_HandR	= 0;
		m_LegL	= 0;
		m_LegR	= 0;
		transparency = 1;
		temp = Vector3(0, 0, 0);
		prevAngle = 0;
		count = 0;
		angleRad = 0;
		nextAngle = 0;
		animate = true;
		prevPos = Vector3(0,0,0);
		rightHand = 0;
		leftHand = 0;
		rightLeg = 0;
		leftLeg = 0;
		moveHand = false;
		moveHandIdle = false;
		attacked = false;
		health = 250;

	};
	~AI(){};
	float getAngle();
	void renderAlien(bool enableLight, MS modelStack, MS viewStack, MS projectionStack, unsigned int m_parameters[25], Mesh ** meshlist);
	void move(Vector3 targetPos, Camera5 camera, Mesh ** meshList, int modelStart, int modelEnd, double time, double dt);
	void attack();
	void animation();
	void damagePlayer();
	Mesh * m_Head;
	Mesh * m_Body;
	Mesh * m_HandL;
	Mesh * m_HandR;
	Mesh * m_LegL;
	Mesh * m_LegR;
	vector<Mesh *> allMesh;
	float transparency;
	bool animate;
	Vector3 position;
	Vector3 temp;
	Vector3 distance;
private:
	float health;
	Vector3 inBetween;
	int count;
	float angleRad;
	float nextAngle;
	float prevAngle;
	Vector3 prevPos;
	PathFinding m_path;
	bool left = true;
	bool right = false;
	//Animation Variables

		//Hand Movements
		bool moveHand;
		bool moveHandIdle;
		float prightHand;
		float rightHand;
		float pleftHand;
		float leftHand;

		//Leg movements
		bool leg = left;
		float rightLeg;
		float prightLeg;
		float leftLeg;
		float pleftLeg;

		//Attack
		bool attacked;
};

#endif