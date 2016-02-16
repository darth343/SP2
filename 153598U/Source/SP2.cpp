#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Application.h"
#include "Camera2.h"
#include "Utility.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using std::cout;
using std::endl;

SP2::SP2()
{
}

SP2::~SP2()
{
}

void SP2::Init()
{
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Use our shader
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_MATERIAL_TRANSPARENCY] = glGetUniformLocation(m_programID, "material.transparency");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(7, 7.4, 39);
	light[0].color.Set(1, 1, 1);
	light[0].power = 3;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(0, 5, -20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//SKY
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//seaback.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//seafront.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//searight.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//sealeft.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//seaup.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//seadown.tga");

	//GROUND
	meshList[GEO_GROUND] = MeshBuilder::GenerateGround("ground", Color(0.2, 0.2, 0.2));
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//sand.tga");

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");
	meshList[GEO_MODEL1]->position.Set(10, 0, 10);
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//wallleft.tga");
	meshList[GEO_MODEL1]->interactable = true;

		
	// Enable blendings
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SP2::Update(double dt)
{
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face cullings
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	cout << "JEFF IS A FAGGOT" << endl;
	camera.Update(dt);

	Movement(dt);

	object = Interaction(dt);
}

Mesh* SP2::Interaction(double dt)
{
	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range ; temp += camera.view.Normalized())
	{
		for (int i = GEO_MODEL1; i < GEO_TEXT; i++) //Anything after GEO_MODEL1, will have collision
		{
			if (meshList[i]->min != nullptr || meshList[i]->max != nullptr)
			{
				if ((temp.x + camera.position.x <= meshList[i]->max->x + meshList[i]->position.x + offset && temp.x + camera.position.x >= meshList[i]->min->x + meshList[i]->position.x - offset) //Check min and max for x
					&& (temp.y + camera.position.y <= meshList[i]->max->y + meshList[i]->position.y + offset && temp.y + camera.position.y >= meshList[i]->min->y + meshList[i]->position.y - offset) //Check min and max for y
					&& (temp.z + camera.position.z <= meshList[i]->max->z + meshList[i]->position.z + offset && temp.z + camera.position.z >= meshList[i]->min->z + meshList[i]->position.z - offset)) //Check min and max for z
				{
					if (meshList[i]->interactable == false)
					{
						return nullptr;
						break;
					}
					else
					{
						return meshList[i];
						break;
					}
				}
			}
		}
	}
	return nullptr;
}
int count = 0;
void SP2::Movement(double dt)
{
	int speed = 15;
	float offset = 2;
	int cameraX = -1;
	
	if (Application::IsKeyPressed('W'))
	{
		if (camera.position.x + camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x + camera.view.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x + camera.view.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset  >= meshList[i]->max->y + meshList[i]->position.y + offset)
					{
						move = true;
					}
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.x += camera.view.Normalized().x * dt * speed;
		}

		if (camera.position.z + camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.view.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z + camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.z += camera.view.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		if (camera.position.x - camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;


			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x - camera.view.Normalized().x * dt * speed * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.x -= camera.view.Normalized().x * dt * speed;
		}
		
		if (camera.position.z - camera.view.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.view.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;


			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z - camera.view.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z - camera.view.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.z -= camera.view.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('A'))
	{
		if (camera.position.x - camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x - camera.right.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x - camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x - camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.x -= camera.right.Normalized().x * dt * speed;
		}
		
		if (camera.position.z - camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z - camera.right.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z - camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z - camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.z -= camera.right.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		if (camera.position.x + camera.right.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.right.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.x + camera.right.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x + camera.right.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.x += camera.right.Normalized().x * dt * speed;
		}
		
		if (camera.position.z + camera.right.Normalized().z * dt * speed + 1 < 498 && camera.position.z + camera.right.Normalized().z * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.x < meshList[i]->min->x + meshList[i]->position.x - offset ||
						camera.position.x > meshList[i]->max->x + meshList[i]->position.x + offset ||
						camera.position.z + camera.right.Normalized().z * dt * speed > meshList[i]->max->z + meshList[i]->position.z + offset ||
						camera.position.z + camera.right.Normalized().z * dt * speed < meshList[i]->min->z + meshList[i]->position.z - offset ||
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 > meshList[i]->max->y + meshList[i]->position.y + offset)
						move = true;
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.z += camera.right.Normalized().z * dt * speed;
		}
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (camera.position.y + camera.position.Normalized().y * dt * speed + 1 < 498 && camera.position.y + camera.position.Normalized().y * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
			{
				if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
				{
					if (camera.position.y + camera.position.Normalized().y * dt * speed < meshList[i]->min->y ||
						camera.position.y + camera.position.Normalized().y * dt * speed > meshList[i]->max->y ||
						camera.position.x < meshList[i]->min->x + meshList[i]->position.x ||
						camera.position.x < meshList[i]->max->x + meshList[i]->position.x ||
						camera.position.z < meshList[i]->min->z + meshList[i]->position.z ||
						camera.position.z < meshList[i]->max->z + meshList[i]->position.z
						)
					{

						move = true;
					}
					else
					{
						move = false;
						break;
					}
				}
				else
				{
					move = true;
				}
			}
			if (move)
				camera.position.y += camera.position.Normalized().y * dt * speed;
		}
	}
	else
	{

		bool fall = false;
		float gravity = dt * 10;
		for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
		{
			if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
			{
				if (camera.position.x  > meshList[i]->position.x + meshList[i]->min->x + offset + 5 &&
					camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset  - 5&&
					camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset + 5 &&
					camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset - 5 &&
					(camera.position.y - gravity) > meshList[i]->position.y + meshList[i]->max->y + 5 )
				{
					cout << "Y POS: " << camera.position.y << " Mesh Y POS: " << meshList[i]->position.y + meshList[i]->max->y + 5 << endl;
					fall = true;
				}
				else if (camera.position.y - gravity > 5 &&
						(camera.position.x < meshList[i]->position.x + meshList[i]->min->x ||
						camera.position.x > meshList[i]->position.x + meshList[i]->max->x ||
						camera.position.z < meshList[i]->position.z + meshList[i]->min->z ||
						camera.position.z > meshList[i]->position.z + meshList[i]->max->z))
				{
					fall = true;
				}
			}
		}
		if (fall == true)
		{
			camera.position.y -= gravity;
		}
	}

}

void SP2::RenderMesh(Mesh * mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once 
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void SP2::RenderSkybox(Vector3 position)
{
	float SkyScale = 500.f;
	float offset = 1;


	//rotateAngle++;
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	//modelStack.Rotate(rotateAngle/5, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -SkyScale / 2 + offset);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, SkyScale / 2 - offset);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(SkyScale / 2 - offset, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);

	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);

	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-SkyScale / 2 + offset, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(-1, 1, 1);
	modelStack.Rotate(90, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, SkyScale / 2 - offset, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -SkyScale / 2 + offset, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5, 0 + 0.5, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SP2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Pass in light position
	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	//Set all matrices to identity
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	////Axes
	RenderMesh(meshList[GEO_AXES], false);

	//Skybox
	RenderSkybox(camera.position);

	//if (object)
	//{
	//	object->light = false;
	//}
	//else
	//{
	//	for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
	//	{
	//		meshList[i]->light = true;
	//	}
	//}
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_MODEL1]->position.x, meshList[GEO_MODEL1]->position.y, meshList[GEO_MODEL1]->position.z);
	RenderMesh(meshList[GEO_MODEL1], true);
	modelStack.PopMatrix();

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Ground


}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
