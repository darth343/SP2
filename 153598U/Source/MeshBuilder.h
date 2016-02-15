#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color);
	static Mesh* GenerateGround(const std::string &meshName, Color color);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices);
	static Mesh* GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float outerR, float innerR);
	static Mesh* GenerateCone(const std::string &meshName, Color color, float radius, float height);
	static Mesh* GenerateWCone(const std::string &meshName, Color color, float lowerRadius, float higherRadius, float height);
	static Mesh* Generate3dQuad(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GeneratePyramid(const std::string &meshName, Color color, float thick, float height, float stretch = 1, float length = 1);
	static Mesh* GenerateRectPrism(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ, float side = 0);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif