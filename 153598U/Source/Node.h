#ifndef NODE_H
#define NODE_H

struct Node
{
	static const int WORLD_SIZE = 1000000;
public:
	int m_X;
	int m_Z;
	int m_id;
	Node * parent;
	float G;
	float H;


	Node() : parent(0) {};
	Node(int x, int z, Node* _parent = 0) : m_X(x), m_Z(z), parent(_parent), m_id(z * WORLD_SIZE + z), G(0), H(0) {};
	~Node(){};

	float getF() { return G + H; };
	float Distance(Node * End)
	{
		float x = this->m_X - End->m_X;
		float z = this->m_Z - End->m_Z;

		return x + z;
	}
};

#endif