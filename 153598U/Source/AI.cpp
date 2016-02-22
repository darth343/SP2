#include "AI.h"

AI::AI()
{
}

AI::~AI()
{
}

void AI::move(Vector3 currentPos, Vector3 targetPos, Camera5 camera,  Mesh ** meshList, int modelStart, int modelEnd, double time)
{
	if (m_path.getPath().size() > 0 && fmod(time, 0.1) < 0.025)
	{
		count++;
		Vector3 temp = m_path.NextPathPos(m_Body);
		Vector3 move(0, 0, 0);
		inBetween = temp - m_Body->position; // vector in between enemy and next path

		angle = atan(inBetween.z / inBetween.x);

		move = temp - m_Head->position;
		m_Head->position += move;
		move = temp - m_Body->position;
		m_Body->position += move;

		move = temp - m_HandL->position;
		m_HandL->position += move;

		move = temp - m_HandR->position;
		m_HandR->position += move;

		move = temp - m_LegL->position;
		m_LegL->position += move;

		move = temp - m_LegR->position;
		m_LegR->position += move;
	}
	if (m_path.getPath().size() <= 1 && Vector3(camera.position - m_Body->position).Length() < 30)
	{
		count = 0;
		if (camera.position != prevPos)
		{
			m_path.m_initializedStartGoal = false;
			m_path.m_found = false;
			m_path.FindPath(m_Body->position, camera.position, meshList, modelStart, modelEnd);
			prevPos = camera.position;
		}
	}
	if (Vector3(camera.position - m_Body->position).Length() > 30)
	{
		transparency = 1;
	}
	else if (Vector3(camera.position - m_Body->position).Length() < 30)
	{
		transparency = (Vector3(camera.position - m_Body->position).Length()) / 30;
		if (Vector3(camera.position - m_Body->position).Length() < 20)
			transparency = fmod((20 / Vector3(camera.position - m_Body->position).Length()), 1);
	}
}

float AI::getAngle()
{
	if (inBetween.x > 0 && inBetween.z > 0) // if facing north east
	{
		//cout << " going north east " << endl;
		//modelStack.Rotate(90 - Math::RadianToDegree(angle), 0, 1, 0);
		prevAngle = 90 - Math::RadianToDegree(angle);
	}
	else if (inBetween.x > 0 && inBetween.z == 0)
	{
		//cout << " going east " << endl;
		//modelStack.Rotate(90, 0, 1, 0);
		prevAngle = 90;
	}
	else if (inBetween.x > 0 && inBetween.z < 0) // if facing south east
	{
		//cout << " going south east " << endl;
		//modelStack.Rotate(180 +  Math::RadianToDegree(angle), 0, 1, 0);
		prevAngle = 180 + Math::RadianToDegree(angle);
	}
	else if (inBetween.x == 0 && inBetween.z < 0)
	{
		//cout << " going south " << endl;
		//modelStack.Rotate(180, 0, 1, 0);
		prevAngle = 180;
	}
	else if (inBetween.x < 0 && inBetween.z < 0) // if facing north
	{
		//cout << " going south west " << endl;
		//modelStack.Rotate(180 + Math::RadianToDegree(angle), 0, 1, 0);
		prevAngle = 180 + Math::RadianToDegree(angle);
	}
	else if (inBetween.x < 0 && inBetween.z == 0) // if facing north
	{
		//cout << " going west " << endl;
		//modelStack.Rotate(270, 0, 1, 0);
		prevAngle = 270;
	}
	else if (inBetween.x < 0 && inBetween.z > 0) // if facing north east
	{
		//cout << " going north west " << endl;
		//modelStack.Rotate(Math::RadianToDegree(angle), 0, 1, 0);
		prevAngle = Math::RadianToDegree(angle);
	}
	else if (inBetween.x == 0 && inBetween.z > 0)
	{
		//cout << " going north " << endl;
		prevAngle = 0;
	}

	return prevAngle;
}