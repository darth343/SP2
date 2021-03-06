/******************************************************************************/
/*!
\file	Node.h
\author Arun Ezekiel
\par	email: 153598U\@mymail.nyp.edu.sg
\brief
Class to define a Node
*/
/******************************************************************************/
#ifndef NODE_H
#define NODE_H
/****************************************************************************/
/*!
Struct Node:
\brief Defines Node with Necessary Values and Functions ( x and z values )
*/
/****************************************************************************/
struct Node
{
	/****************************************************************************/
	/*!
	World Size, to be used for giving unique ID's
	*/
	/****************************************************************************/
	static const int WORLD_SIZE = 100;
public:
	/****************************************************************************/
	/*!
	X value of Node
	*/
	/****************************************************************************/
	int m_X;
	/****************************************************************************/
	/*!
	Z value of Node
	*/
	/****************************************************************************/
	int m_Z;
	/****************************************************************************/
	/*!
	Unique ID of Node
	*/
	/****************************************************************************/
	int m_id;
	/****************************************************************************/
	/*!
	Parented Node
	*/
	/****************************************************************************/
	Node * parent;
	/****************************************************************************/
	/*!
	G value ( Cost to move )
	*/
	/****************************************************************************/
	float G;
	/****************************************************************************/
	/*!
	H value ( Shortest Cost from current position to goal )
	*/
	/****************************************************************************/
	float H;

	/****************************************************************************/
	/*!
	Constructs Node with null pointer parent
	*/
	/****************************************************************************/
	Node() : parent(0) {};
	/****************************************************************************/
	/*!
	\brief
	Overloaded Node Constructor
	\param x, z, _parent
	Constructs Node with passed in x, z, parent. Gives Node unique ID and sets G and H to 0
	*/
	/****************************************************************************/
	Node(float x, float z, Node* _parent = 0) : m_X(x), m_Z(z), parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};

	~Node(){};
	/****************************************************************************/
	/*!
	\brief
	Return F value of Node
	Returns calculated F value
	*/
	/****************************************************************************/
	float getF() { return G + H; };
	/****************************************************************************/
	/*!
	\brief
	Manhattan Distance Function
	\param End
	Returns calculated distance value
	*/
	/****************************************************************************/
	float Distance(Node * End)
	{
		float x = (float)(fabs(float(this->m_X - End->m_X)));
		float z = (float)(fabs(float(this->m_Z - End->m_Z)));

		return x + z;
	}
};

#endif