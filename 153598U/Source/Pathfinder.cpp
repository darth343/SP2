#include "Pathfinder.h"
#include "SP2.h"
#include "fstream"
#include <iostream>
PathFinding::PathFinding()
{
	m_initializedStartGoal = false;
	m_found = false;
}

PathFinding::~PathFinding()
{
}
void PathFinding::FindPath(Vector3 currentPos, Vector3 targetPos, Mesh ** meshList, int modelStart, int modelEnd)
{
		for (int i = 0; i < 75; i++)
		{
			if (!m_initializedStartGoal)
			{
				// Clear All Vector Pointers DELETE before clearing ( Memory Leak Prevention)

				for (int i = 0; i < m_openList.size(); i++)
				{
					delete m_openList[i];
				}
				m_openList.clear();

				for (int i = 0; i < m_visitedList.size(); i++)
				{
					delete m_visitedList[i];
				}
				m_visitedList.clear();

				for (int i = 0; i < m_pathToGoal.size(); i++)
				{
					delete m_pathToGoal[i];
				}
				m_pathToGoal.clear();

				//Initialize Start
				Node start;
				start.m_X = currentPos.x;
				start.m_Z = currentPos.z;
				y = currentPos.y;
				Node goal;
				goal.m_X = targetPos.x;
				goal.m_Z = targetPos.z;
				SetStartAndGoal(start, goal);
				m_initializedStartGoal = true;
				Starter = modelStart;
				Ender = modelEnd;
			}
			if (m_initializedStartGoal)
			{
				ContinuePath(meshList);
				if (m_found == true)
				{
					break;
				}
			}
		}
}

void PathFinding::SetStartAndGoal(Node start, Node goal)
{
	start.m_X = start.m_X - (fmod(start.m_X, 2));
	start.m_Z = start.m_Z - (fmod(start.m_Z, 2));
	goal.m_X = goal.m_X - (fmod(goal.m_X, 2));
	goal.m_Z = goal.m_Z - (fmod(goal.m_Z, 2));
	m_start = new Node(start.m_X, start.m_Z, NULL);
	m_goal = new Node(goal.m_X, goal.m_Z, &goal);

	m_start->G = 0;
	m_start->H = m_start->Distance(m_goal);
	m_start->parent = 0;
	m_openList.push_back(m_start);
}

Node * PathFinding::getNextCell()
{
	float bestF = 999999;
	int nodeIndex = -1;

	Node * nextNode = nullptr;

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->getF() < bestF)
		{
			bestF = m_openList[i]->getF();
			nodeIndex = i;
		}
	}

	if (nodeIndex >= 0)
	{
		nextNode = m_openList[nodeIndex];
		m_visitedList.push_back(nextNode);
		m_openList.erase(m_openList.begin() + nodeIndex);
	}
	return nextNode;
}

void PathFinding::PathOpened(int x, int z, float newCost, Node * parent, Mesh ** meshList)
{
	int offset = 1;
	for (int i = Starter; i < Ender; i++)
	{
		if (meshList[i]->min == nullptr || meshList[i]->max == nullptr)
		{
			break;
		}
		if (
			x > meshList[i]->position.x + meshList[i]->min->x - offset &&
			x < meshList[i]->position.x + meshList[i]->max->x + offset &&
			z > meshList[i]->position.z + meshList[i]->min->z - offset &&
			z < meshList[i]->position.z + meshList[i]->max->z + offset &&
			y > meshList[i]->position.y + meshList[i]->min->y - offset &&
			y < meshList[i]->position.y + meshList[i]->max->y + offset
			)
		{
			return;
		}
	}
	int id = z * Node::WORLD_SIZE + x;
	for (int i = 0; i < m_visitedList.size(); i++)
	{
		if (id == m_visitedList[i]->m_id)
		{
			return;
		}
	}

	Node * newChild = new Node(x, z, parent);
	newChild->G = newCost;
	newChild->H = parent->Distance(m_goal);

	for (int i = 0; i < m_openList.size(); i++)
	{
		if (id == m_openList[i]->m_id)
		{
			float newF = newChild->G + newCost + m_openList[i]->H;
			if (m_openList[i]->getF() > newF) // if F is smaller than current node's f
			{
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else // if F is not better
			{
				delete newChild;
				return;
			}
		}
	}
	m_openList.push_back(newChild);
}

void PathFinding::ContinuePath(Mesh ** meshList)
{
	if (m_openList.empty())
	{
		return;
	}

	Node * currentNode = getNextCell();

	if (currentNode->m_id == m_goal->m_id)
	{
		m_goal->parent = currentNode->parent;
		Node * getPath;
		for (getPath = m_goal; getPath != NULL; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new Vector3(getPath->m_X, 0, getPath->m_Z));
		}

		m_found = true;
		return;
	}
	else
	{
		int blockSize = 2;

		//right side
		PathOpened(currentNode->m_X + blockSize, currentNode->m_Z, currentNode->G + 2 ,currentNode, meshList);

		//left side
		PathOpened(currentNode->m_X - blockSize, currentNode->m_Z, currentNode->G + 2, currentNode, meshList);

		//above
		PathOpened(currentNode->m_X, currentNode->m_Z + blockSize, currentNode->G + 2, currentNode, meshList);

		//bottom
		PathOpened(currentNode->m_X, currentNode->m_Z - blockSize, currentNode->G + 2, currentNode, meshList);

		//left-above diagonal

		PathOpened(currentNode->m_X - blockSize, currentNode->m_Z + blockSize, currentNode->G + 2.83, currentNode, meshList);

		//right-above diagonal

		PathOpened(currentNode->m_X + blockSize, currentNode->m_Z + blockSize, currentNode->G + 2.83, currentNode, meshList);

		//left-down diagonal

		PathOpened(currentNode->m_X - blockSize, currentNode->m_Z - blockSize, currentNode->G + 2.83, currentNode, meshList);

		//right-down diagonal

		PathOpened(currentNode->m_X + blockSize, currentNode->m_Z - blockSize, currentNode->G + 2.83, currentNode, meshList);

		for (int i = 0; i < m_openList.size(); i++)
		{
			if (currentNode->m_id == m_openList[i]->m_id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}
}

Vector3 PathFinding::NextPathPos(Mesh * theMesh)
{
	int index = 1;

	Vector3 nextPos;
	nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
	nextPos.z = m_pathToGoal[m_pathToGoal.size() - index]->z;
	Vector3 distance = nextPos - theMesh->position;

	if (index < m_pathToGoal.size())
	{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
	}
	return nextPos;
}
