#include "Vertex.h"
#include "MeshBuilder.h"
#include <GL\glew.h>
#include <MyMath.h>
#include <vector>
#include "LoadOBJ.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	v.pos.Set(-lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, -lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, lengthY, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, -lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, lengthZ);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	//const GLfloat vertex_buffer_data[] = {
	//	-1000, 0, 0,
	//	1000, 0, 0,
	//	0, -1000, 0,
	//	0, 1000, 0,
	//	0, 0, -1000,
	//	0, 0, 1000,
	//};
	//const GLfloat color_buffer_data[] = {
	//	1, 0, 0,
	//	1, 0, 0,
	//	0, 1, 0,
	//	0, 1, 0,
	//	0, 0, 1,
	//	0, 0, 1,
	//};
	//const GLuint index_buffer_data[] = {
	//	0, 1,
	//	2, 3, 
	//	4, 5,
	//};

	Mesh *mesh = new Mesh(meshName);


	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 6;
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//top
	v.pos.Set(0.5f, 0.f, 0.5f);   	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, 0.5f);	    v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(1, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, 0.5f);  	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 1);	vertex_buffer_data.push_back(v);

	
	
	

	for (unsigned i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateGround(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//top
	v.pos.Set(0.5f, 0.f, 0.5f);   	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(10, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(10, 10);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.f, 0.5f);	    v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(10, 10);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.f, 0.5f);  	v.color = color;	v.normal.Set(0, 1, 0); v.texCoord.Set(0, 10);	vertex_buffer_data.push_back(v);





	for (unsigned i = 0; i < 6; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	//left
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	//back
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	//bottom
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	//front
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float CircleX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}

float CircleZ(float theta)
{
	return sin(Math::DegreeToRadian(theta));
}



Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex V;

	float anglePerSlice = 360.f / numSlices;

	for (unsigned slice = 0; slice < numSlices+1; ++slice)
	{
		float theta = anglePerSlice * slice;
		V.pos.Set(CircleX(theta), 0, CircleZ(theta));
		V.normal.Set(0, 1, 0);
		V.color = color;
		vertex_buffer_data.push_back(V);
	}

	V.pos.Set(0, 0, 0);
	V.normal.Set(0, 1, 0);
	V.color = color;

	vertex_buffer_data.push_back(V);

	for (int i = 0; i < numSlices+1; i++)
	{
		index_buffer_data.push_back(i);
		index_buffer_data.push_back(numSlices + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, float innerRadius, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex V;

	float anglePerSlice = 360.f / numSlices;

	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = anglePerSlice * slice;
		V.pos.Set(CircleX(theta), 0, CircleZ(theta));
		V.normal.Set(0, 1, 0);
		V.color = color;
		vertex_buffer_data.push_back(V);

		V.pos.Set(CircleX(theta) * innerRadius, 0, CircleZ(theta) * innerRadius);
		V.normal.Set(0, 1, 0);
		V.color = color;
		vertex_buffer_data.push_back(V);
	}

	for (int i = 0; i < numSlices + 1; i++)
	{
		index_buffer_data.push_back(2 * i);
		index_buffer_data.push_back(2 * i + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

float SphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}

float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex V;

	float anglePerStack = 180.f / numStacks;
	float anglePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90.f + stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = anglePerSlice * slice;
			V.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			V.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			V.color = color;
			vertex_buffer_data.push_back(V);
		}
	}

	//V.pos.Set(0, 0, 0);
	//V.color = color;

	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (int i = 0; i < numSlices + 1; i++)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + i);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + i);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float outerR, float innerR)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex V;

	float anglePerStack = 360.f / numStacks;
	float anglePerSlice = 360.f / numSlices;

	float x1, z1;

	float x2, y2, z2;

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			z1 = outerR * cos(Math::DegreeToRadian(stack * anglePerStack) );
			x1 = outerR * sin(Math::DegreeToRadian(stack * anglePerStack));
			z2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * anglePerSlice)) ) * cos( Math::DegreeToRadian (stack * anglePerStack) );
			y2 = innerR * sin(Math::DegreeToRadian(slice * anglePerSlice));
			x2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * anglePerSlice))) * sin(Math::DegreeToRadian(stack * anglePerStack));

			V.pos.Set(x2, y2, z2);
			V.color = color;
			V.normal.Set(x2 - x1, y2, z2 - z1);
			vertex_buffer_data.push_back(V);
		}
	}

	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (int i = 0; i < numSlices + 1; i++)
		{
			index_buffer_data.push_back((numSlices + 1) * stack + i + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + i + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float ConeX(float radius, float theta)
{
	return (radius*cos(Math::DegreeToRadian(theta)));
}

float ConeZ(float radius, float theta)
{
	return (radius *sin(Math::DegreeToRadian(theta)));
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, float radius, float height)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	for (float theta = 0; theta <= 360; theta += 10) //Slice
	{
		v.pos.Set(ConeX(radius, theta) , -height / 2, ConeZ(radius, theta));
		v.color = color;
		v.normal.Set(ConeX(radius, theta), -height / 2, ConeZ(radius, theta));
		vertex_buffer_data.push_back(v);
		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, height / 2, 0);
		vertex_buffer_data.push_back(v);
	}
	

	for (float theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		v.normal.Set(0, -height / 2, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 1000; ++i) {
		index_buffer_data.push_back(i);

	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateWCone(const std::string &meshName, Color color, float lowerRadius, float higherRadius, float height)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	for (float theta = 360; theta >=0; theta -= 60)
	{
		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(lowerRadius * cos(Math::DegreeToRadian(theta)), height / 2, lowerRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 30) //Slice
	{
		v.pos.Set(ConeX(higherRadius, theta), -height / 2, ConeZ(higherRadius, theta));
		v.color = color;
		v.normal.Set(ConeX(higherRadius, theta), -height / 2, ConeZ(higherRadius, theta));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
		v.pos.Set(ConeX(lowerRadius, theta), height / 2, ConeZ(lowerRadius, theta));
		v.color = color;
		v.normal.Set(ConeX(higherRadius, theta), -height / 2, ConeZ(higherRadius, theta));
		vertex_buffer_data.push_back(v);
	}


	for (float theta = 0; theta <= 360; theta += 30)
	{
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
		v.pos.Set(higherRadius * cos(Math::DegreeToRadian(theta)), -height / 2, higherRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 1000; ++i) {
		index_buffer_data.push_back(i);

	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}


Mesh* MeshBuilder::Generate3dQuad(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
	//left															//left
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(1, 0, 0);  vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//back															//back
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	//bottom 														//bottom 
	v.pos.Set(lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, -lengthZ); v.color = color;		v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	//front	  														//front	  
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 0, 1);		vertex_buffer_data.push_back(v);
	//right	   														//right	   
	v.pos.Set(lengthX, -lengthY, -lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, -lengthY, -lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(-1, 0, 0);		vertex_buffer_data.push_back(v);
	//top	   														//top	   
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		v.normal.Set(0, 1, 0);		vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GeneratePyramid(const std::string &meshName, Color color, float thick, float height, float stretch, float length)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	// Front						
	v.pos.Set(0.0f, height, stretch);	 v.normal.Set(0.0f, 0.0f, 1.0f); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(-thick, -height, length);	 v.normal.Set(0.0f, 0.0f, 1.0f); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, length);	 v.normal.Set(0.0f, 0.0f, 1.0f); v.color = color; vertex_buffer_data.push_back(v);

	// Right						
	v.pos.Set(0.0f, height, -stretch);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, height, stretch);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, length);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
															 
	v.pos.Set(thick, -height, -length);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, height, -stretch);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, length);	 v.normal.Set(thick, height, length); v.color = color; vertex_buffer_data.push_back(v);

	// Back							
	v.pos.Set(0.0f, height, -stretch);	 v.normal.Set(0.0f, 0.0f, -1.0f); v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, -length);	 v.normal.Set(0.0f, 0.0f, -1.0f); v.color = color;	vertex_buffer_data.push_back(v);
	v.pos.Set(-thick, -height, -length); v.normal.Set(0.0f, 0.0f, -1.0f); v.color = color;	vertex_buffer_data.push_back(v);

	// Left
	v.pos.Set(-thick, -height, length);	 v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, height, -stretch);	 v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(-thick, -height, -length); v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);

	v.pos.Set(-thick, -height, length);	 v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, height, stretch);	 v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f, height, -stretch);	 v.normal.Set(-thick, height, length); v.color = color; vertex_buffer_data.push_back(v);


	// Bottom
	v.pos.Set(-thick, -height, length);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-thick, -height, -length);v.color = color;    v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, length);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-thick, -height, -length);v.color = color;    v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, -length);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(thick, -height, length);	v.color = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRectPrism(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ, float side)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;

	//left															  	//left															
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;  	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(-lengthX, lengthY, lengthZ); v.normal.Normalize(); vertex_buffer_data.push_back(v);
	//back															  	//front	  												
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX + side, -lengthY, -lengthZ);	v.color = color;  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;  	v.normal.Set(0, 0, -1); vertex_buffer_data.push_back(v);
	//bottom 														  	//bottom 														
	v.pos.Set(lengthX + side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX + side, -lengthY, -lengthZ);	v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX + side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, -lengthZ); v.color = color;  	v.normal.Set(0, -1, 0); vertex_buffer_data.push_back(v);
	//front	  														  	//front	  														
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);	 
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX + side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX - side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX + side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	//right	   														  	//right	   														
	v.pos.Set(lengthX + side, -lengthY, -lengthZ);	v.color = color;  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);	 
	v.pos.Set(lengthX + side, -lengthY, lengthZ);	v.color = color;  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);	 
	v.pos.Set(lengthX + side, -lengthY, -lengthZ);	v.color = color;  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(lengthX, lengthY, lengthZ); vertex_buffer_data.push_back(v);	  
	//top	   														  	//top	   														
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);	 
	v.pos.Set(lengthX, lengthY, -lengthZ);	v.color = color;			v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, -lengthZ);	v.color = color;		  	v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-lengthX, lengthY, lengthZ);	v.color = color;		  	v.normal.Set(0, 1, 0); vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
		//Read vertices, texcoords & normals from OBJ
		std::vector<Position> vertices;
		std::vector<TexCoord> uvs;
		std::vector<Vector3> normals;
		bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
		if (!success)
			return NULL;

		std::ifstream fileStream(file_path, std::ios::binary);
		if (!fileStream.is_open())
		{
			std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
			return false;
		}

		Vector3 minimum(9999, 9999, 9999);
		Vector3 maximum(-9999, -9999, -9999);

		while (!fileStream.eof()) {
			char buf[256];
			fileStream.getline(buf, 256);
			if (strncmp("v ", buf, 2) == 0) { //process vertex position

				Position vertex;
				sscanf_s((buf + 2), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);

				if (vertex.x < minimum.x)
					minimum.x = vertex.x;
				
				if (vertex.y < minimum.y)
					minimum.y = vertex.y;

				if (vertex.z < minimum.z)
					minimum.z = vertex.z;

				if (vertex.x > maximum.x)
					maximum.x = vertex.x;

				if (vertex.y > maximum.y)
					maximum.y = vertex.y;

				if (vertex.z > maximum.z)
					maximum.z = vertex.z;
			}
		}

		//Index the vertices, texcoords & normals properly
		std::vector<Vertex> vertex_buffer_data;
		std::vector<GLuint> index_buffer_data;
		IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
		//Create the mesh and call glBindBuffer, glBufferData
		//Use triangle list and remember to set index size

		const Vector3 dMin = minimum;
		const Vector3 dMax = maximum;


		Mesh *mesh = new Mesh(meshName);
		mesh->min = new Vector3(minimum);
		mesh->Pmin = new Vector3(dMin);
		mesh->max = new Vector3(maximum);
		mesh->Pmax = new Vector3(dMax);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

		mesh->indexSize = index_buffer_data.size();
		mesh->mode = Mesh::DRAW_TRIANGLES;

		return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	//top
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	float offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			v.pos.Set(0.5f, 0.5f, 0.f);			v.texCoord.Set((j + 1) * width, 1.f - i * width);				vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, -0.5f, 0.f);		v.texCoord.Set((j+1) * width, 1.f - (i + 1) * width);			vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, -0.5f, 0.f);		v.texCoord.Set(j * width, 1.f - (i + 1) * width);				vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, 0.5f, 0.f);		v.texCoord.Set(j * width, 1.f - i * width);						vertex_buffer_data.push_back(v);


			//Task: Add 4 vertices into vertex_buffer_data

			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(2 + offset);
			index_buffer_data.push_back(1 + offset);
			index_buffer_data.push_back(0 + offset);
			index_buffer_data.push_back(3 + offset);
			index_buffer_data.push_back(2 + offset);
			offset += 4;
		}
	}


	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;

}