#include "Pathfinder.h"

PathFinding::PathFinding()
{
	m_initializedStartGoal = false;
	m_found = false;
}

PathFinding::~PathFinding()
{
}
void PathFinding::FindPath(Vector3 currentPos, Vector3 targetPos)
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

		for (int i = 0; m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		//Initialize Start
		Node start;
		start.m_X = currentPos.x;
		start.m_Z = currentPos.z;

		Node goal;
		goal.m_X = targetPos.x;
		goal.m_Z = targetPos.z;
		SetStartAndGoal(start, goal);
		m_initializedStartGoal = true;
	}
	if (m_initializedStartGoal)
	{
		//ContinuePath();
	}
}

void PathFinding::SetStartAndGoal(Node start, Node goal)
{
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

void PathFinding::PathOpened(int x, int z, float newCost, Node * parent)
{
	//int id = z  * Node::WORLD_SIZE + x;
	//for (int i = 0; i < m_visitedList.size(); i++)
	//{
	//	if (id == m_visitedList[i]->m_id)
	//	{
	//		return;
	//	}
	//}

	//Node * newChild = new Node(x, z, parent);
	//newChild->G = newCost;
	//newChild->H = parent->Distance(m_goal);

	//for (int i = 0; i < m_openList.size(); i++)
	//{
	//}
}