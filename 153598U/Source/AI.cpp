#include "AI.h"
#include "SP2.h"
#include <sstream>
#include "GL\glew.h"
int AI::deathCount = 0;
void AI::move(Vector3 targetPos, Camera5 camera, Mesh ** meshList, int modelStart, int modelEnd, double time, double dt, Player & player)
{
	if (!isDead())
	{
		distance = Vector3(camera.position - position);
		if (distance.Length() > 30)
		{
			return;
		}
		if (m_path.getPath().size() > 0)
		{
			int speed = 20;
			Vector3 move(0, 0, 0);
			if ((static_cast<int>(position.x) >= temp.x - 1 &&
				static_cast<int>(position.x) <= temp.x + 1) &&
				(static_cast<int>(position.z) >= temp.z - 1 &&
				static_cast<int>(position.z) <= temp.z + 1))
			{
				temp = m_path.NextPathPos(m_Body);
			}
			else
			{
				if (distance.Length() > 12)
				{
					animate = true;
					move = temp - position;
					move.y = 0;
					position += move.Normalized() * dt * speed;
					inBetween = temp - position; // vector in between enemy and next path
					angleRad = atan(inBetween.z / inBetween.x);
				}
				else
				{
					inBetween = camera.position - position; // vector in between enemy and next path
					angleRad = atan(inBetween.z / inBetween.x);
				}
			}
		}
		if (m_path.getPath().size() <= 1 && (distance.Length() < 30 && distance.Length() > 13))
		{
			if (camera.position != prevPos)
			{
				m_path.m_initializedStartGoal = false;
				m_path.m_found = false;;
				m_path.FindPath(position, camera.position, meshList, modelStart, modelEnd);
				prevPos = camera.position;
			}
		}
		if (m_path.getPath().size() <= 1)
		{
			animate = false;
		}
		if (distance.Length() > 40)
		{
			transparency = 1;
		}
		else if (distance.Length() < 40)
		{
			transparency = (distance.Length()) / 40;
			if (distance.Length() < 30)
				transparency = fmod((30 / distance.Length()), 1);
		}

		animation(dt, player);
	}
}

float AI::getAngle()
{
	if (!isDead())
	{
		if (inBetween.x > 0 && inBetween.z > 0)
		{
			nextAngle = 90 - Math::RadianToDegree(angleRad);
		}
		else if (inBetween.x > 0 && inBetween.z < 0)
		{
			nextAngle = 90 - Math::RadianToDegree(angleRad);
		}
		else if (inBetween.x < 0 && inBetween.z < 0)
		{
			nextAngle = 270 - Math::RadianToDegree(angleRad);
		}
		else if (inBetween.x < 0 && inBetween.z > 0)
		{
			nextAngle = 270 - Math::RadianToDegree(angleRad);
		}
		else if (inBetween.x == 0 && inBetween.z > 0)
		{
			nextAngle = 0;
		}
		else if (inBetween.x == 0 && inBetween.z < 0)
		{
			nextAngle = 180;
		}
		else if (inBetween.x > 0 && inBetween.z == 0)
		{
			nextAngle = 90;
		}
		else if (inBetween.x < 0 && inBetween.z == 0)
		{
			nextAngle = 270;
		}

		Mtx44 rotation;
		rotation.SetToRotation(nextAngle - prevAngle, 0, 1, 0);

		if (prevAngle != nextAngle)
		{
			// Head HitBox Rotation
			*m_Head->min = rotation * (*m_Head->min);
			*m_Head->max = rotation * (*m_Head->max);
			if (m_Head->min->x > m_Head->max->x)
			{
				float x = m_Head->min->x;
				Vector3 * temp1 = m_Head->max;
				m_Head->min->x = m_Head->max->x;
				m_Head->max->x = x;
			}
			if (m_Head->min->y > m_Head->max->y)
			{
				float y = m_Head->min->y;
				m_Head->min->y = m_Head->max->y;
				m_Head->max->y = y;
			}
			if (m_Head->min->z > m_Head->max->z)
			{
				float z = m_Head->min->z;
				m_Head->min->z = m_Head->max->z;
				m_Head->max->z = z;
			}

			// Body HitBox Rotation
			*m_Body->min = rotation * (*m_Body->min);
			*m_Body->max = rotation * (*m_Body->max);
			if (m_Body->min->x > m_Body->max->x)
			{
				float x = m_Body->min->x;
				Vector3 * temp1 = m_Body->max;
				m_Body->min->x = m_Body->max->x;
				m_Body->max->x = x;
			}
			if (m_Body->min->y > m_Body->max->y)
			{
				float y = m_Body->min->y;
				m_Body->min->y = m_Body->max->y;
				m_Body->max->y = y;
			}
			if (m_Body->min->z > m_Body->max->z)
			{
				float z = m_Body->min->z;
				m_Body->min->z = m_Body->max->z;
				m_Body->max->z = z;
			}

			// Right Hand HitBox Rotation
			*m_HandR->min = rotation * (*m_HandR->min);
			*m_HandR->max = rotation * (*m_HandR->max);
			if (m_HandR->min->x > m_HandR->max->x)
			{
				float x = m_HandR->min->x;
				Vector3 * temp1 = m_HandR->max;
				m_HandR->min->x = m_HandR->max->x;
				m_HandR->max->x = x;
			}
			if (m_HandR->min->y > m_HandR->max->y)
			{
				float y = m_HandR->min->y;
				m_HandR->min->y = m_HandR->max->y;
				m_HandR->max->y = y;
			}
			if (m_HandR->min->z > m_HandR->max->z)
			{
				float z = m_HandR->min->z;
				m_HandR->min->z = m_HandR->max->z;
				m_HandR->max->z = z;
			}

			// Left Hand HitBox Rotation
			*m_HandL->min = rotation * (*m_HandL->min);
			*m_HandL->max = rotation * (*m_HandL->max);
			if (m_HandL->min->x > m_HandL->max->x)
			{
				float x = m_HandL->min->x;
				Vector3 * temp1 = m_HandL->max;
				m_HandL->min->x = m_HandL->max->x;
				m_HandL->max->x = x;
			}
			if (m_HandL->min->y > m_HandL->max->y)
			{
				float y = m_HandL->min->y;
				m_HandL->min->y = m_HandL->max->y;
				m_HandL->max->y = y;
			}
			if (m_HandL->min->z > m_HandL->max->z)
			{
				float z = m_HandL->min->z;
				m_HandL->min->z = m_HandL->max->z;
				m_HandL->max->z = z;
			}

			// Right Leg HitBox Rotation
			*m_LegR->min = rotation * (*m_LegR->min);
			*m_LegR->max = rotation * (*m_LegR->max);
			if (m_LegR->min->x > m_LegR->max->x)
			{
				float x = m_LegR->min->x;
				Vector3 * temp1 = m_LegR->max;
				m_LegR->min->x = m_LegR->max->x;
				m_LegR->max->x = x;
			}
			if (m_LegR->min->y > m_LegR->max->y)
			{
				float y = m_LegR->min->y;
				m_LegR->min->y = m_LegR->max->y;
				m_LegR->max->y = y;
			}
			if (m_LegR->min->z > m_LegR->max->z)
			{
				float z = m_LegR->min->z;
				m_LegR->min->z = m_LegR->max->z;
				m_LegR->max->z = z;
			}

			// Left Leg HitBox Rotation
			*m_LegL->min = rotation * (*m_LegL->min);
			*m_LegL->max = rotation * (*m_LegL->max);
			if (m_LegL->min->x > m_LegL->max->x)
			{
				float x = m_LegL->min->x;
				Vector3 * temp1 = m_LegL->max;
				m_LegL->min->x = m_LegL->max->x;
				m_LegL->max->x = x;
			}
			if (m_LegL->min->y > m_LegL->max->y)
			{
				float y = m_LegL->min->y;
				m_LegL->min->y = m_LegL->max->y;
				m_LegL->max->y = y;
			}
			if (m_LegL->min->z > m_LegL->max->z)
			{
				float z = m_LegL->min->z;
				m_LegL->min->z = m_LegL->max->z;
				m_LegL->max->z = z;
			}
		}
	}
	prevAngle = nextAngle;
	return nextAngle;
}

void AI::renderAlien(bool enableLight, MS modelStack, MS viewStack, MS projectionStack, unsigned int m_parameters[25], Mesh ** meshlist, Player &player)
{
	if (!isDead())
	{
		std::ostringstream hpDp;
		hpDp << "HP: " << health;
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y + 10, position.z);
		modelStack.Rotate(getAngle(), 0, 1, 0);
		SP2::RenderText(meshlist[145], hpDp.str(), Color(1, 0.5, 0.5), modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		glUniform1f(m_parameters[7], transparency);
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		//modelStack.Translate(position.x, m_Head->position.y, m_Head->position.z);
		modelStack.Rotate(getAngle(), 0, 1, 0);
		SP2::RenderMesh(m_Head, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		modelStack.PushMatrix();
		//modelStack.Translate(position.x, position.y, position.z);
		SP2::RenderMesh(m_Body, enableLight, modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//modelStack.Translate(m_HandL->position.x, m_HandL->position.y, m_HandL->position.z);
		modelStack.Translate(0, 6.5, 0);
		modelStack.Rotate(leftHand, 1, 0, 0);
		modelStack.Translate(0, -6.5, 0);
		SP2::RenderMesh(m_HandL, enableLight, modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//modelStack.Translate(m_HandR->position.x, m_HandR->position.y, m_HandR->position.z);
		modelStack.Translate(0, 6.5, 0);
		modelStack.Rotate(rightHand, 1, 0, 0);
		modelStack.Translate(0, -6.5, 0);
		SP2::RenderMesh(m_HandR, enableLight, modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//modelStack.Translate(m_LegL->position.x, m_LegL->position.y, m_LegL->position.z);
		modelStack.Translate(0, 3.7, 0);
		modelStack.Rotate(leftLeg, 1, 0, 0);
		modelStack.Translate(0, -3.7, 0);
		SP2::RenderMesh(m_LegL, enableLight, modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//modelStack.Translate(m_LegR->position.x, m_LegR->position.y, m_LegR->position.z);
		modelStack.Translate(0, 3.7, 0);
		modelStack.Rotate(rightLeg, 1, 0, 0);
		modelStack.Translate(0, -3.7, 0);
		SP2::RenderMesh(m_LegR, enableLight, modelStack, viewStack, projectionStack, m_parameters);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
		glUniform1f(m_parameters[7], 1);
	}
	else
	{
		if (deathAngle < 90)
		{
			deathAngle+=10;
		}
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z);
		modelStack.Rotate(getAngle(), 0, 1, 0);
		modelStack.Rotate(deathAngle, deathPivot.x, deathPivot.y, deathPivot.z);
		SP2::RenderMesh(m_Head, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		SP2::RenderMesh(m_Body, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		SP2::RenderMesh(m_HandL, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		SP2::RenderMesh(m_HandR, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		SP2::RenderMesh(m_LegL, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		SP2::RenderMesh(m_LegR, enableLight, modelStack, viewStack, projectionStack, m_parameters);

		modelStack.PopMatrix();
	}
}

void AI::animation(double dt, Player & player)
{
	int animationSpeed = 150;
	if (animate)
	{
		if (moveHand == false)
		{
			if (leftHand < 120)
			{
				leftHand += animationSpeed * dt;
			}
			if (rightHand < 120)
			{
				rightHand += animationSpeed * dt;
			}
			if (leftHand >= 120 && rightHand >= 120)
			{
				moveHand = true;
			}
		}

		if (distance.Length() > 13)
		{
			if (moveHandIdle == true)
			{
				if (leftHand > 105)
				{
					leftHand -= animationSpeed * dt;
				}
				if (rightHand < 135)
				{
					rightHand += animationSpeed * dt;
				}
				if (leftHand <= 105 && rightHand >= 135)
				{
					moveHandIdle = false;
				}
			}
			else
			{
				if (rightHand > 105)
				{
					rightHand -= animationSpeed * dt;
				}
				if (leftHand < 135)
				{
					leftHand += animationSpeed * dt;
				}
				if (rightHand <= 105 && leftHand >= 135)
				{
					moveHandIdle = true;
				}
			}
			if (leg == left)
			{
				if (leftLeg > -35)
				{
					leftLeg -= animationSpeed * dt;
				}
				if (rightLeg < 35)
				{
					rightLeg += animationSpeed * dt;
				}
				if (leftLeg <= -35 && rightLeg >= 35)
				{
					leg = right;
				}
			}
			else if (leg == right)
			{
				if (rightLeg > -35)
				{
					rightLeg -= animationSpeed * dt;
				}
				if (leftLeg < 35)
				{
					leftLeg += animationSpeed * dt;
				}
				if (rightLeg <= -35 && leftLeg >= 35)
				{
					leg = left;
				}
			}
		}
	}

	else
	{
		if (leftHand > 0)
		{
			leftHand -= animationSpeed * dt;
		}
		if (rightHand > 0)
		{
			rightHand -= animationSpeed * dt;
		}
		if (rightLeg > 0)
		{
			rightLeg -= animationSpeed * dt;
		}
		if (leftLeg > 0)
		{
			leftLeg -= animationSpeed * dt;
		}
		moveHand = false;
	}
	if (distance.Length() == 13)
	{
		rightHand = 0;
		leftHand = 0;
	}
	if (distance.Length() < 12)
	{
		int AtkSpeed = 1500;
		if (attacked == false)
		{
			if (rightHand > -90)
			{
				rightHand -= AtkSpeed * dt;
			}
			if (leftHand > -90)
			{
				leftHand -= AtkSpeed * dt;
			}
			if (rightHand <= -90 && leftHand <= -90)
			{
				attacked = true;
				damagePlayer(player);
			}
		}
		else
		{
			if (rightHand < 0)
			{
				rightHand += AtkSpeed * dt;
			}
			if (leftHand < 0)
			{
				leftHand += AtkSpeed * dt;
			}
			if (rightHand >= 0 && leftHand >= 0)
			{
				attacked = false;
			}
		}
	}
}

void AI::damagePlayer(Player & player)
{
	if (distance.Length() < 13)
	{
		player.Health -= 3;
	}
}

void AI::deathAnimation(double dt, Camera5 camera)
{
	Vector3 temporary = camera.position - position;
	Mtx44 rotation;
	rotation.SetToRotation(-90, 0, 1, 0);
	temporary = rotation * temporary;
	deathPivot = temporary;
}