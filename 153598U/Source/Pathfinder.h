/******************************************************************************/
/*!
\file	Pathfinder.h
\author Arun Ezekiel
\par	email: 153598U\@mymail.nyp.edu.sg
\brief
Class to define Pathfinding algorithm
*/
/******************************************************************************/
#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <vector>
#include "Vector3.h"
#include "Node.h"
#include "Mesh.h"
using std::vector;
/****************************************************************************/
/*!
Class Pathfinding:
\brief Defines Pathfinding with functions and variables
*/
/****************************************************************************/
class PathFinding
{
public:
	PathFinding();
	~PathFinding();
	/****************************************************************************/
	/*!
	Finds a path to the player
	*/
	/****************************************************************************/
	void FindPath(Vector3 currentPos, Vector3 targetPos, Mesh ** meshList, int modelStart, int modelEnd);
	/****************************************************************************/
	/*!
	Gets the position of the next path
	*/
	/****************************************************************************/
	Vector3 NextPathPos(Mesh * theMesh);
	/****************************************************************************/
	/*!
	Clears the Open List
	*/
	/****************************************************************************/
	void ClearOpenList() { m_openList.clear(); };
	/****************************************************************************/
	/*!
	Clears Visited List
	*/
	/****************************************************************************/
	void ClearVisitedList() { m_visitedList.clear(); };
	/****************************************************************************/
	/*!
	Clears Path to goal
	*/
	/****************************************************************************/
	void ClearPathToGoal() { m_pathToGoal.clear(); };
	/****************************************************************************/
	/*!
	Continues path, for pathfinding
	*/
	/****************************************************************************/
	void ContinuePath(Mesh ** meshList);
	/****************************************************************************/
	/*!
	boolean check if start and goal are initialized
	*/
	/****************************************************************************/
	bool m_initializedStartGoal;
	/****************************************************************************/
	/*!
	boolean check if path is found
	*/
	/****************************************************************************/
	bool m_found;
	/****************************************************************************/
	/*!
	Returns path found
	*/
	/****************************************************************************/
	vector<Vector3*> getPath() { return m_pathToGoal; };
	/****************************************************************************/
	/*!
	Path to goal
	*/
	/****************************************************************************/
	vector<Vector3*> m_pathToGoal;
	/****************************************************************************/
	/*!
	Visited List
	*/
	/****************************************************************************/
	vector<Node*> m_visitedList;
	/****************************************************************************/
	/*!
	Open List
	*/
	/****************************************************************************/
	vector<Node*> m_openList;
private:
	/****************************************************************************/
	/*!
	Set start and goal
	*/
	/****************************************************************************/
	void SetStartAndGoal(Node start, Node goal);
	/****************************************************************************/
	/*!
	Opens path Adjacent to current processing position
	*/
	/****************************************************************************/
	void PathOpened(int x, int z, float newCost, Node * parent, Mesh ** meshList);
	/****************************************************************************/
	/*!
	Gets the best F value Cell
	*/
	/****************************************************************************/
	Node * getNextCell();
	/****************************************************************************/
	/*!
	Start Node
	*/
	/****************************************************************************/
	Node * m_start;
	/****************************************************************************/
	/*!
	Goal Node
	*/
	/****************************************************************************/
	Node * m_goal;
	/****************************************************************************/
	/*!
	Y axis the Aliens are on
	*/
	/****************************************************************************/
	float y;
	/****************************************************************************/
	/*!
	Enum value of Start of Mesh List Object Checking
	*/
	/****************************************************************************/
	int Starter;
	/****************************************************************************/
	/*!
	Enum value of End of Mesh List Object Checking
	*/
	/****************************************************************************/
	int Ender;
};
#endif