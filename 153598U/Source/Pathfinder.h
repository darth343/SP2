#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "Vector3.h"
#include "Node.h"
#include "Mesh.h"
using std::vector;
class PathFinding
{
public:
	PathFinding();
	~PathFinding();

	void FindPath(Vector3 currentPos, Vector3 targetPos, Mesh ** meshList, int modelStart, int modelEnd);
	Vector3 NextPathPos(Mesh * theMesh);
	void ClearOpenList() { m_openList.clear(); };
	void ClearVisitedList() { m_visitedList.clear(); };
	void ClearPathToGoal() { m_pathToGoal.clear(); };
	void ContinuePath(Mesh ** meshList);
	bool m_initializedStartGoal;
	bool m_found;
	vector<Vector3*> getPath() { return m_pathToGoal; };
	void removeStep();
	vector<Vector3*> m_pathToGoal;
	vector<Node*> m_visitedList;
	vector<Node*> m_openList;
private:
	void SetStartAndGoal(Node start, Node goal);
	void PathOpened(int x, int z, float newCost, Node * parent, Mesh ** meshList);
	Node * getNextCell();

	Node * m_start;
	Node * m_goal;

	int Starter;
	int Ender;
};
#endif