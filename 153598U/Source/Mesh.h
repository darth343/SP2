#ifndef MESH_H
#define MESH_H

#include <string>
#include "Material.h"
#include "Vector3.h"

/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{

public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,

		DRAW_MODE_LAST,
	};

	Mesh(const std::string &meshName = "");
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);
	const std::string name;
	DRAW_MODE mode;
	unsigned textureID;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	Vector3 * Pmin;
	Vector3 * min;
	Vector3 * Pmax;
	Vector3 * max;
	Vector3 position;
	Material material;
	bool light;
	bool interactable;
	bool shootable;
	float health=100;
	bool lookAtShop;
	bool ifShootable;
};

#endif