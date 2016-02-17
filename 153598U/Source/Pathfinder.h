#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "Vector3.h"
#include "Node.h"
using std::vector;
class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void FindPath(Vector3 currentPos, Vector3 targetPos);
	Vector3 NextPathPos();
	void ClearOpenList() { m_openList.clear(); };
	void ClearVisitedList() { m_visitedList.clear(); };
	void ClearPathToGoal() { m_pathToGoal.clear(); };
	bool m_initializedStartGoal;
	bool m_found;
private:
	void SetStartAndGoal(Node start, Node goal);
	void PathOpened(int x, int z, float newCost, Node * parent);
	Node * getNextCell();
	//	void ContinuePath();

	Node * m_start;
	Node * m_goal;

	vector<Node*> m_openList;
	vector<Node*> m_visitedList;
	vector<Vector3*> m_pathToGoal;
};
#endif