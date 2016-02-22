#ifndef NODE_H
#define NODE_H

struct Node
{
	static const int WORLD_SIZE = 100;
public:
	int m_X;
	int m_Z;
	int m_id;
	Node * parent;
	float G;
	float H;


	Node() : parent(0) {};
	Node(float x, float z, Node* _parent = 0) : m_X(x), m_Z(z), parent(_parent), m_id(z * WORLD_SIZE + x), G(0), H(0) {};
	~Node(){};

	float getF() { return G + H; };
	float Distance(Node * End)
	{
		float x = (float)(fabs(float(this->m_X - End->m_X)));
		float z = (float)(fabs(float(this->m_Z - End->m_Z)));

		return x + z;
	}
};

#endif