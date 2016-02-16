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
	camera.Init(Vector3(0, 5, -497), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//SKY
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//pink_planet_neg_x.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//pink_planet_pos_x.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//pink_planet_pos_y.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//pink_planet_neg_y.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//pink_planet_pos_z.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//pink_planet_neg_z.tga");

	//GROUND
	meshList[GEO_GROUND] = MeshBuilder::GenerateGround("ground", Color(0.2, 0.2, 0.2));
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//sand.tga");

	//Arun's Wall
	//meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");
	meshList[GEO_FUEL1] = MeshBuilder::GenerateQuad("fuel1", Color(0.8, 0, 0));
	meshList[GEO_FUEL2] = MeshBuilder::GenerateQuad("fuel2", Color(1, 0, 0));
	meshList[GEO_FUEL3] = MeshBuilder::GenerateQuad("fuel3", Color(0, 0.8, 0));
	meshList[GEO_FUEL4] = MeshBuilder::GenerateQuad("fuel4", Color(0, 1, 0));
	meshList[GEO_FUEL5] = MeshBuilder::GenerateQuad("fuel5", Color(0.2,1, 0.2));
	meshList[GEO_JETPACKUI] = MeshBuilder::GenerateQuad("Jetpack UI", Color(1, 2, 1));

	////GROUND
	meshList[GEO_GROUND] = MeshBuilder::GenerateGround("ground", Color(0.2, 0.2, 0.2));
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//sand.tga");

	//STARTLINE
	meshList[GEO_STARTLINE] = MeshBuilder::GenerateQuad("startline", Color(0.8, 0.0, 0.2));
	meshList[GEO_STARTLINE]->position.Set(0, 0, -480);

	//Arun Wall Left
	meshList[GEO_LEFTWALL1] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL1]->position.Set(20, 0, 0);
	meshList[GEO_LEFTWALL1]->interactable = true;

	meshList[GEO_LEFTWALL2] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL2]->position.Set(20, 0, 35);
	meshList[GEO_LEFTWALL2]->interactable = true;

	meshList[GEO_LEFTWALL3] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL3]->position.Set(20, 0, 70);
	meshList[GEO_LEFTWALL3]->interactable = true;

	meshList[GEO_LEFTWALL4] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL4]->position.Set(20, 0, 105);
	meshList[GEO_LEFTWALL4]->interactable = true;

	meshList[GEO_LEFTWALL5] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL5]->position.Set(20, 0, 140);
	meshList[GEO_LEFTWALL5]->interactable = true;

	meshList[GEO_LEFTWALL6] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL6]->position.Set(20, 0, 175);
	meshList[GEO_LEFTWALL6]->interactable = true;

	meshList[GEO_LEFTWALL7] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL7]->position.Set(20, 0, 210);
	meshList[GEO_LEFTWALL7]->interactable = true;

	meshList[GEO_LEFTWALL8] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL8]->position.Set(20, 0, 245);
	meshList[GEO_LEFTWALL8]->interactable = true;

	meshList[GEO_LEFTWALL9] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL9]->position.Set(20, 0, 280);
	meshList[GEO_LEFTWALL9]->interactable = true;

	meshList[GEO_LEFTWALL10] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL10]->position.Set(20, 0, 315);
	meshList[GEO_LEFTWALL10]->interactable = true;

	meshList[GEO_LEFTWALL11] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL11]->position.Set(20, 0, 350);
	meshList[GEO_LEFTWALL11]->interactable = true;

	meshList[GEO_LEFTWALL12] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL12]->position.Set(20, 0, 385);
	meshList[GEO_LEFTWALL12]->interactable = true;

	meshList[GEO_LEFTWALL13] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL13]->position.Set(20, 0, 420);
	meshList[GEO_LEFTWALL13]->interactable = true;

	meshList[GEO_LEFTWALL14] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL14]->position.Set(20, 0, 455);
	meshList[GEO_LEFTWALL14]->interactable = true;

	meshList[GEO_LEFTWALL15] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL15]->position.Set(20, 0, 490);
	meshList[GEO_LEFTWALL15]->interactable = true;

	meshList[GEO_LEFTWALL16] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL16]->position.Set(20, 0, -35);
	meshList[GEO_LEFTWALL16]->interactable = true;

	meshList[GEO_LEFTWALL17] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL17]->position.Set(20, 0, -70);
	meshList[GEO_LEFTWALL17]->interactable = true;

	meshList[GEO_LEFTWALL18] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL18]->position.Set(20, 0, -105);
	meshList[GEO_LEFTWALL18]->interactable = true;

	meshList[GEO_LEFTWALL19] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL19]->position.Set(20, 0, -140);
	meshList[GEO_LEFTWALL19]->interactable = true;

	meshList[GEO_LEFTWALL20] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL20]->position.Set(20, 0, -175);
	meshList[GEO_LEFTWALL20]->interactable = true;

	meshList[GEO_LEFTWALL21] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL21]->position.Set(20, 0, -210);
	meshList[GEO_LEFTWALL21]->interactable = true;

	meshList[GEO_LEFTWALL22] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL22]->position.Set(20, 0, -245);
	meshList[GEO_LEFTWALL22]->interactable = true;

	meshList[GEO_LEFTWALL23] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL23]->position.Set(20, 0, -280);
	meshList[GEO_LEFTWALL23]->interactable = true;

	meshList[GEO_LEFTWALL24] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL24]->position.Set(20, 0, -315);
	meshList[GEO_LEFTWALL24]->interactable = true;

	meshList[GEO_LEFTWALL25] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL25]->position.Set(20, 0, -350);
	meshList[GEO_LEFTWALL25]->interactable = true;

	meshList[GEO_LEFTWALL26] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL26]->position.Set(20, 0, -385);
	meshList[GEO_LEFTWALL26]->interactable = true;

	meshList[GEO_LEFTWALL27] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL27]->position.Set(20, 0, -420);
	meshList[GEO_LEFTWALL27]->interactable = true;

	meshList[GEO_LEFTWALL28] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL28]->position.Set(20, 0, -455);
	meshList[GEO_LEFTWALL28]->interactable = true;

	meshList[GEO_LEFTWALL29] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[GEO_LEFTWALL29]->position.Set(20, 0, -490);
	meshList[GEO_LEFTWALL29]->interactable = true;


	//Arun Wall Right
	meshList[GEO_RIGHTWALL1] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL1]->position.Set(-20, 0, 0);
	meshList[GEO_RIGHTWALL1]->interactable = true;

	meshList[GEO_RIGHTWALL2] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL2]->position.Set(-20, 0, 35);
	meshList[GEO_RIGHTWALL2]->interactable = true;

	meshList[GEO_RIGHTWALL3] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL3]->position.Set(-20, 0, 70);
	meshList[GEO_RIGHTWALL3]->interactable = true;

	meshList[GEO_RIGHTWALL4] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL4]->position.Set(-20, 0, 105);
	meshList[GEO_RIGHTWALL4]->interactable = true;

	meshList[GEO_RIGHTWALL5] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL5]->position.Set(-20, 0, 140);
	meshList[GEO_RIGHTWALL5]->interactable = true;

	meshList[GEO_RIGHTWALL6] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL6]->position.Set(-20, 0, 175);
	meshList[GEO_RIGHTWALL6]->interactable = true;

	meshList[GEO_RIGHTWALL7] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL7]->position.Set(-20, 0, 210);
	meshList[GEO_RIGHTWALL7]->interactable = true;

	meshList[GEO_RIGHTWALL8] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL8]->position.Set(-20, 0, 245);
	meshList[GEO_RIGHTWALL8]->interactable = true;

	meshList[GEO_RIGHTWALL9] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL9]->position.Set(-20, 0, 280);
	meshList[GEO_RIGHTWALL9]->interactable = true;

	meshList[GEO_RIGHTWALL10] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL10]->position.Set(-20, 0, 315);
	meshList[GEO_RIGHTWALL10]->interactable = true;

	meshList[GEO_RIGHTWALL11] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL11]->position.Set(-20, 0, 350);
	meshList[GEO_RIGHTWALL11]->interactable = true;

	meshList[GEO_RIGHTWALL12] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL12]->position.Set(-20, 0, 385);
	meshList[GEO_RIGHTWALL12]->interactable = true;

	meshList[GEO_RIGHTWALL13] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL13]->position.Set(-20, 0, 420);
	meshList[GEO_RIGHTWALL13]->interactable = true;

	meshList[GEO_RIGHTWALL14] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL14]->position.Set(-20, 0, 455);
	meshList[GEO_RIGHTWALL14]->interactable = true;

	meshList[GEO_RIGHTWALL15] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL15]->position.Set(-20, 0, 490);
	meshList[GEO_RIGHTWALL15]->interactable = true;

	meshList[GEO_RIGHTWALL16] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL16]->position.Set(-20, 0, -35);
	meshList[GEO_RIGHTWALL16]->interactable = true;

	meshList[GEO_RIGHTWALL17] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL17]->position.Set(-20, 0, -70);
	meshList[GEO_RIGHTWALL17]->interactable = true;

	meshList[GEO_RIGHTWALL18] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL18]->position.Set(-20, 0, -105);
	meshList[GEO_RIGHTWALL18]->interactable = true;

	meshList[GEO_RIGHTWALL19] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL19]->position.Set(-20, 0, -140);
	meshList[GEO_RIGHTWALL19]->interactable = true;

	meshList[GEO_RIGHTWALL20] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL20]->position.Set(-20, 0, -175);
	meshList[GEO_RIGHTWALL20]->interactable = true;

	meshList[GEO_RIGHTWALL21] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL21]->position.Set(-20, 0, -210);
	meshList[GEO_RIGHTWALL21]->interactable = true;

	meshList[GEO_RIGHTWALL22] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL22]->position.Set(-20, 0, -245);
	meshList[GEO_RIGHTWALL22]->interactable = true;

	meshList[GEO_RIGHTWALL23] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL23]->position.Set(-20, 0, -280);
	meshList[GEO_RIGHTWALL23]->interactable = true;

	meshList[GEO_RIGHTWALL24] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL24]->position.Set(-20, 0, -315);
	meshList[GEO_RIGHTWALL24]->interactable = true;

	meshList[GEO_RIGHTWALL25] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL25]->position.Set(-20, 0, -350);
	meshList[GEO_RIGHTWALL25]->interactable = true;

	meshList[GEO_RIGHTWALL26] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL26]->position.Set(-20, 0, -385);
	meshList[GEO_RIGHTWALL26]->interactable = true;

	meshList[GEO_RIGHTWALL27] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL27]->position.Set(-20, 0, -420);
	meshList[GEO_RIGHTWALL27]->interactable = true;

	meshList[GEO_RIGHTWALL28] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL28]->position.Set(-20, 0, -455);
	meshList[GEO_RIGHTWALL28]->interactable = true;

	meshList[GEO_RIGHTWALL29] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[GEO_RIGHTWALL29]->position.Set(-20, 0, -490);
	meshList[GEO_RIGHTWALL29]->interactable = true;

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");

	meshList[GEO_MODEL1]->position.Set(10, 0, 10);
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//wallleft.tga");
	meshList[GEO_MODEL1]->interactable = true;

	//Map(FreeRun)

	//Blocks
	meshList[GEO_BLOCK1] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK1]->position.Set(10, 3, -440);
	meshList[GEO_BLOCK1]->interactable = true;

	meshList[GEO_BLOCK2] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK2]->position.Set(-10, 3, -420);
	meshList[GEO_BLOCK2]->interactable = true;

	meshList[GEO_BLOCK3] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK3]->position.Set(10, 3, -220);
	meshList[GEO_BLOCK3]->interactable = true;

	meshList[GEO_BLOCK4] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK4]->position.Set(10, 3, -200);
	meshList[GEO_BLOCK4]->interactable = true;

	meshList[GEO_BLOCK5] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK5]->position.Set(-10, 3, -220);
	meshList[GEO_BLOCK5]->interactable = true;

	meshList[GEO_BLOCK6] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK6]->position.Set(-10, 3, -200);
	meshList[GEO_BLOCK6]->interactable = true;

	meshList[GEO_BLOCK7] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK7]->position.Set(0, 3, -180);
	meshList[GEO_BLOCK7]->interactable = true;

	meshList[GEO_BLOCK8] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK8]->position.Set(10, 3, 60);
	meshList[GEO_BLOCK8]->interactable = true;

	meshList[GEO_BLOCK9] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK9]->position.Set(-10, 3, 60);
	meshList[GEO_BLOCK9]->interactable = true;

	meshList[GEO_BLOCK10] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[GEO_BLOCK10]->position.Set(0, 3, 80);
	meshList[GEO_BLOCK10]->interactable = true;

	//Wall(Thin)
	meshList[GEO_THIN1] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[GEO_THIN1]->position.Set(0, 3, -350);
	meshList[GEO_THIN1]->interactable = true;

	meshList[GEO_THIN2] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[GEO_THIN2]->position.Set(0, 3, -150);
	meshList[GEO_THIN2]->interactable = true;

	meshList[GEO_THIN3] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[GEO_THIN3]->position.Set(0, 3, 40);
	meshList[GEO_THIN3]->interactable = true;

	//Wall(Thin)2
	meshList[GEO_THINz1] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz1]->position.Set(0, 3, 0);
	meshList[GEO_THINz1]->interactable = true;

	meshList[GEO_THINz2] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz2]->position.Set(10, 3, 0);
	meshList[GEO_THINz2]->interactable = true;

	meshList[GEO_THINz3] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz3]->position.Set(-10, 3, 0);
	meshList[GEO_THINz3]->interactable = true;

	meshList[GEO_THINz4] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz4]->position.Set(5, 3, 30);
	meshList[GEO_THINz4]->interactable = true;

	meshList[GEO_THINz5] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz5]->position.Set(15, 3, 30);
	meshList[GEO_THINz5]->interactable = true;

	meshList[GEO_THINz6] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz6]->position.Set(-5, 3, 30);
	meshList[GEO_THINz6]->interactable = true;

	meshList[GEO_THINz7] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz7]->position.Set(-15, 3, 30);
	meshList[GEO_THINz7]->interactable = true;

	meshList[GEO_THINz8] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz8]->position.Set(10, 3, 80);
	meshList[GEO_THINz8]->interactable = true;

	meshList[GEO_THINz9] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[GEO_THINz9]->position.Set(-10, 3, 80);
	meshList[GEO_THINz9]->interactable = true;


	//Wall(Thick)
	meshList[GEO_THICK1] = MeshBuilder::GenerateOBJ("Wall(Thick)", "OBJ//Wall(Thick).obj");
	meshList[GEO_THICK1]->position.Set(0, 3, -400);
	meshList[GEO_THICK1]->interactable = true;

	meshList[GEO_THICK2] = MeshBuilder::GenerateOBJ("Wall(Thick)", "OBJ//Wall(Thick).obj");
	meshList[GEO_THICK2]->position.Set(0, 3, -50);
	meshList[GEO_THICK2]->interactable = true;

	//TEXT
	meshList[GEO_TIMEDISPLAY] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TIMEDISPLAY]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_JETPACKUI] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_JETPACKUI]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TIME] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TIME]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_ENEMYHEALTH] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_ENEMYHEALTH]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_ENEMYHEALTHDISPLAY] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_ENEMYHEALTHDISPLAY]->textureID = LoadTGA("Image//calibri.tga");
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
	time += dt;
	camera.Update(dt);
	//Movement(dt);
	Vector3 bulletSpeed = (0.1, 0.1, 0.1);
	//bullet = camera.view;
	if (Application::IsKeyPressed(VK_LBUTTON) && time > delay)
	{
		temp.Position = camera.position;
		temp.start = temp.Position;
		temp.trajectory = camera.view.Normalized();
		temp.object = Shooting(dt);
		bullets.push_back(temp);
		delay = time + 0.1;
	}
	float bulletspeed = 0.5;
	for (amtBullet = 0; amtBullet < bullets.size(); amtBullet++)
	{
		
		bullets[amtBullet].Position.x += bullets[amtBullet].trajectory.Normalized().x * bulletspeed;
		bullets[amtBullet].Position.y += bullets[amtBullet].trajectory.Normalized().y * bulletspeed;
		bullets[amtBullet].Position.z += bullets[amtBullet].trajectory.Normalized().z * bulletspeed;
		//cout << bullets[0].Position << endl;
		if (bullets[amtBullet].object)
		{
			int offset = 10;
			if ((bullets[amtBullet].Position.x > bullets[amtBullet].object->min->x - offset && bullets[amtBullet].Position.x < bullets[amtBullet].object->max->x + offset) &&
				(bullets[amtBullet].Position.y > bullets[amtBullet].object->min->y - offset&& bullets[amtBullet].Position.x < bullets[amtBullet].object->max->y + offset) &&
				(bullets[amtBullet].Position.z > bullets[amtBullet].object->min->z - offset&& bullets[amtBullet].Position.x < bullets[amtBullet].object->max->z + offset)
				)
			{
				cout << "hit" << endl;
				bullets[amtBullet].object->health -= 10;
				if (bullets[amtBullet].object->health <= 0)
				{
					objectDied = true;
					bullets[amtBullet].object->health = 0;
				}
				bullets.erase(bullets.begin() + amtBullet);
			}
		}
		else
		{
			if (Vector3(bullets[amtBullet].Position - bullets[amtBullet].start).Length() >= 100)
			{
				bullets.erase(bullets.begin() + amtBullet);
			}
		}
	}

	CharacMovement(dt);

	object = Interaction(dt);
}

Mesh* SP2::Shooting(double dt)
{
	float range = 1000;
	float offset = 0.5;

	for (Vector3 temp = camera.view*0.001; temp.Length() <= range; temp += camera.view.Normalized())
	{
		for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
		{
			if (meshList[i]->min != nullptr || meshList[i]->max != nullptr)
			{
				if ((temp.x + camera.position.x <= meshList[i]->max->x + meshList[i]->position.x + offset && temp.x + camera.position.x >= meshList[i]->min->x + meshList[i]->position.x - offset)
					&& (temp.y + camera.position.y <= meshList[i]->max->y + meshList[i]->position.y + offset && temp.y + camera.position.y >= meshList[i]->min->y + meshList[i]->position.y - offset)
					&& (temp.z + camera.position.z <= meshList[i]->max->z + meshList[i]->position.z + offset && temp.z + camera.position.z >= meshList[i]->min->z + meshList[i]->position.z - offset))
				{
					if (meshList[i]->shootable == false)
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
}// bad shooting*/ // mesh shooting
Mesh* SP2::Interaction(double dt)
{
	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range ; temp += camera.view.Normalized())
	{
		for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)

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

void SP2::Movement(double dt)
{
	int speed = 50;

	float offset = 2;
	int cameraX = -1;
	int grav = 1;
	
	///////////////////////////////////////////////////////////////////////////
	//					JETPACK												//
	//																	    //
	/////////////////////////////////////////////////////////////////////////
	fuel += 0.5;
	if (Application::IsKeyPressed(VK_SPACE) && Application::IsKeyPressed(VK_LCONTROL) &&fuel>0)
	{

			camera.position.Set(camera.position.x, camera.position.y + dt * 8, camera.position.z);
			fuel -= 0.08;
			//std::cout << fuel;
	}

	else
	{
		if (fuel <100)
		{
		fuel =fuel+1;
		std::cout << fuel << endl;
			if (fuel >=100)
			{
			fuel = 100;
			}
		}
		if (camera.position.y >= 5)
		{
			camera.position.Set(camera.position.x, camera.position.y + dt *(-9-(grav*10)), camera.position.z);
			grav++;
		}
		
		
	}
	
	///////////////////////////////////////////////////////////////////////////
	//					CAMERA												//
	//																	    //
	/////////////////////////////////////////////////////////////////////////
	if (Application::IsKeyPressed('W'))
	{
		if (camera.position.x + camera.view.Normalized().x * dt * speed + 1 < 498 && camera.position.x + camera.view.Normalized().x * dt * speed - 1 > -498)
		{
			bool move = false;
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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


			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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


			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
			for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
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
}

void SP2::CharacMovement(double dt)
{
	int speed = 10;
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
					if (camera.position.z < meshList[i]->min->z + meshList[i]->position.z - offset ||  //Check min and max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.z > meshList[i]->max->z + meshList[i]->position.z + offset || //Check max for z axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed < meshList[i]->min->x + meshList[i]->position.x - offset || //Check min for x axis. If bigger than min, smaller than max, walk = false 
						camera.position.x + camera.view.Normalized().x * dt * speed > meshList[i]->max->x + meshList[i]->position.x + offset || //Check max for x axis. If bigger than min, smaller than max, walk = false 
						0 < meshList[i]->min->y + meshList[i]->position.y - offset ||
						camera.position.y - 5 + offset >= meshList[i]->max->y + meshList[i]->position.y + offset)
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
						camera.position.y - 5 + offset> meshList[i]->max->y + meshList[i]->position.y + offset)
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
						camera.position.y - 5 + offset> meshList[i]->max->y + meshList[i]->position.y + offset)
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
		for (int i = GEO_MODEL1; i < GEO_TEXT; i++)
		{
			if (meshList[i]->min != nullptr && meshList[i]->max != nullptr)
			{
				if (camera.position.x  > meshList[i]->position.x + meshList[i]->min->x + offset - 3.8 &&
					camera.position.x < meshList[i]->position.x + meshList[i]->max->x - offset + 3.8 &&
					camera.position.z > meshList[i]->position.z + meshList[i]->min->z + offset - 3.8 &&
					camera.position.z < meshList[i]->position.z + meshList[i]->max->z - offset + 3.8
					)
				{
					if (camera.position.y - 5 - gravity > meshList[i]->position.y + meshList[i]->max->y)
					{
						fall = true;
					}
					else
					{
						fall = false;
						break;
					}
				}
				else
				{
					fall = true;
				}
			}
		}
		if (fall == true && camera.position.y - 5 - gravity > 0)
		{
			gravity += dt;
			camera.position.y -= gravity;
		}
		else
		{
			gravity = 10 * dt;
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

void SP2::RenderOBJonScreen(Mesh* mesh, float sizex,float sizey, float x, float y)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
	//Mtx44 projection;
	//ortho.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);

	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	//modelStack.PushMatrix();
	modelStack.Translate(x, y, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(sizex, sizey,1);
	////modelStack.Translate(camera.position.x + camera.view.x, camera.position.y + camera.view.y, camera.position.z + camera.view.z);
	//modelStack.Translate(camera.view.x, camera.view.y + camera.position.y, camera.view.z);
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(mesh, false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

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

	//Axes
	RenderMesh(meshList[GEO_AXES], false);

	//Skybox
	RenderSkybox(camera.position);

	/*if (object)
	{
		object->light = false;
	}
	else
	{
		for (int i = GEO_LEFTWALL1; i < GEO_TEXT; i++)
		{
			meshList[i]->light = true;
		}
	}*/

	//Ground
	modelStack.PushMatrix();
	modelStack.Scale(1500, 1500, 1500);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	if (bullets.size() != NULL)
	{
		for (int a = 0; a <bullets.size(); a++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(bullets[a].Position.x, bullets[a].Position.y, bullets[a].Position.z);
			modelStack.Scale(0.1, 0.1,0.1);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}

	}
	//Arun's Wall
	//STARTLINE
	modelStack.PushMatrix();
	modelStack.Scale(40, 10, 5);
	RenderMesh(meshList[GEO_STARTLINE], true);
	modelStack.PopMatrix();

	//Arun's Wall Left
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL1]->position.x, meshList[GEO_LEFTWALL1]->position.y, meshList[GEO_LEFTWALL1]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL2]->position.x, meshList[GEO_LEFTWALL2]->position.y, meshList[GEO_LEFTWALL2]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL3]->position.x, meshList[GEO_LEFTWALL3]->position.y, meshList[GEO_LEFTWALL3]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL4]->position.x, meshList[GEO_LEFTWALL4]->position.y, meshList[GEO_LEFTWALL4]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL5]->position.x, meshList[GEO_LEFTWALL5]->position.y, meshList[GEO_LEFTWALL5]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL6]->position.x, meshList[GEO_LEFTWALL6]->position.y, meshList[GEO_LEFTWALL6]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL7]->position.x, meshList[GEO_LEFTWALL7]->position.y, meshList[GEO_LEFTWALL7]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL8]->position.x, meshList[GEO_LEFTWALL8]->position.y, meshList[GEO_LEFTWALL8]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL9]->position.x, meshList[GEO_LEFTWALL9]->position.y, meshList[GEO_LEFTWALL9]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL9], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL10]->position.x, meshList[GEO_LEFTWALL10]->position.y, meshList[GEO_LEFTWALL10]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL10], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL11]->position.x, meshList[GEO_LEFTWALL11]->position.y, meshList[GEO_LEFTWALL11]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL11], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL12]->position.x, meshList[GEO_LEFTWALL12]->position.y, meshList[GEO_LEFTWALL12]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL12], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL13]->position.x, meshList[GEO_LEFTWALL13]->position.y, meshList[GEO_LEFTWALL13]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL13], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL14]->position.x, meshList[GEO_LEFTWALL14]->position.y, meshList[GEO_LEFTWALL14]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL14], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL15]->position.x, meshList[GEO_LEFTWALL15]->position.y, meshList[GEO_LEFTWALL15]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL15], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL16]->position.x, meshList[GEO_LEFTWALL16]->position.y, meshList[GEO_LEFTWALL16]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL16], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL17]->position.x, meshList[GEO_LEFTWALL17]->position.y, meshList[GEO_LEFTWALL17]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL17], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL18]->position.x, meshList[GEO_LEFTWALL18]->position.y, meshList[GEO_LEFTWALL18]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL18], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL19]->position.x, meshList[GEO_LEFTWALL19]->position.y, meshList[GEO_LEFTWALL19]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL19], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL20]->position.x, meshList[GEO_LEFTWALL20]->position.y, meshList[GEO_LEFTWALL20]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL20], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL21]->position.x, meshList[GEO_LEFTWALL21]->position.y, meshList[GEO_LEFTWALL21]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL21], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL22]->position.x, meshList[GEO_LEFTWALL22]->position.y, meshList[GEO_LEFTWALL22]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL22], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL23]->position.x, meshList[GEO_LEFTWALL23]->position.y, meshList[GEO_LEFTWALL23]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL23], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL24]->position.x, meshList[GEO_LEFTWALL24]->position.y, meshList[GEO_LEFTWALL24]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL24], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL25]->position.x, meshList[GEO_LEFTWALL25]->position.y, meshList[GEO_LEFTWALL25]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL25], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL26]->position.x, meshList[GEO_LEFTWALL26]->position.y, meshList[GEO_LEFTWALL26]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL26], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL27]->position.x, meshList[GEO_LEFTWALL27]->position.y, meshList[GEO_LEFTWALL27]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL27], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL28]->position.x, meshList[GEO_LEFTWALL28]->position.y, meshList[GEO_LEFTWALL28]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL28], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTWALL29]->position.x, meshList[GEO_LEFTWALL29]->position.y, meshList[GEO_LEFTWALL29]->position.z);
	RenderMesh(meshList[GEO_LEFTWALL29], true);
	modelStack.PopMatrix();
	

	//Arun's Wall Right
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL1]->position.x, meshList[GEO_RIGHTWALL1]->position.y, meshList[GEO_RIGHTWALL1]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL2]->position.x, meshList[GEO_RIGHTWALL2]->position.y, meshList[GEO_RIGHTWALL2]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL3]->position.x, meshList[GEO_RIGHTWALL3]->position.y, meshList[GEO_RIGHTWALL3]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL4]->position.x, meshList[GEO_RIGHTWALL4]->position.y, meshList[GEO_RIGHTWALL4]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL5]->position.x, meshList[GEO_RIGHTWALL5]->position.y, meshList[GEO_RIGHTWALL5]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL6]->position.x, meshList[GEO_RIGHTWALL6]->position.y, meshList[GEO_RIGHTWALL6]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL7]->position.x, meshList[GEO_RIGHTWALL7]->position.y, meshList[GEO_RIGHTWALL7]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL8]->position.x, meshList[GEO_RIGHTWALL8]->position.y, meshList[GEO_RIGHTWALL8]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL9]->position.x, meshList[GEO_RIGHTWALL9]->position.y, meshList[GEO_RIGHTWALL9]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL9], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL10]->position.x, meshList[GEO_RIGHTWALL10]->position.y, meshList[GEO_RIGHTWALL10]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL10], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL11]->position.x, meshList[GEO_RIGHTWALL11]->position.y, meshList[GEO_RIGHTWALL11]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL11], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL12]->position.x, meshList[GEO_RIGHTWALL12]->position.y, meshList[GEO_RIGHTWALL12]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL12], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL13]->position.x, meshList[GEO_RIGHTWALL13]->position.y, meshList[GEO_RIGHTWALL13]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL13], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL14]->position.x, meshList[GEO_RIGHTWALL14]->position.y, meshList[GEO_RIGHTWALL14]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL14], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL15]->position.x, meshList[GEO_RIGHTWALL15]->position.y, meshList[GEO_RIGHTWALL15]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL15], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL16]->position.x, meshList[GEO_RIGHTWALL16]->position.y, meshList[GEO_RIGHTWALL16]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL16], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL17]->position.x, meshList[GEO_RIGHTWALL17]->position.y, meshList[GEO_RIGHTWALL17]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL17], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL18]->position.x, meshList[GEO_RIGHTWALL18]->position.y, meshList[GEO_RIGHTWALL18]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL18], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL19]->position.x, meshList[GEO_RIGHTWALL19]->position.y, meshList[GEO_RIGHTWALL19]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL19], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL20]->position.x, meshList[GEO_RIGHTWALL20]->position.y, meshList[GEO_RIGHTWALL20]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL20], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL21]->position.x, meshList[GEO_RIGHTWALL21]->position.y, meshList[GEO_RIGHTWALL21]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL21], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL22]->position.x, meshList[GEO_RIGHTWALL22]->position.y, meshList[GEO_RIGHTWALL22]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL22], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL23]->position.x, meshList[GEO_RIGHTWALL23]->position.y, meshList[GEO_RIGHTWALL23]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL23], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL24]->position.x, meshList[GEO_RIGHTWALL24]->position.y, meshList[GEO_RIGHTWALL24]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL24], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL25]->position.x, meshList[GEO_RIGHTWALL25]->position.y, meshList[GEO_RIGHTWALL25]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL25], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL26]->position.x, meshList[GEO_RIGHTWALL26]->position.y, meshList[GEO_RIGHTWALL26]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL26], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL27]->position.x, meshList[GEO_RIGHTWALL27]->position.y, meshList[GEO_RIGHTWALL27]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL27], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL28]->position.x, meshList[GEO_RIGHTWALL28]->position.y, meshList[GEO_RIGHTWALL28]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL28], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTWALL29]->position.x, meshList[GEO_RIGHTWALL29]->position.y, meshList[GEO_RIGHTWALL29]->position.z);
	RenderMesh(meshList[GEO_RIGHTWALL29], true);
	modelStack.PopMatrix();

	//Block
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK1]->position.x, meshList[GEO_BLOCK1]->position.y, meshList[GEO_BLOCK1]->position.z);
	RenderMesh(meshList[GEO_BLOCK1], meshList[GEO_BLOCK1]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK2]->position.x, meshList[GEO_BLOCK2]->position.y, meshList[GEO_BLOCK2]->position.z);
	RenderMesh(meshList[GEO_BLOCK2], meshList[GEO_BLOCK2]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK3]->position.x, meshList[GEO_BLOCK2]->position.y, meshList[GEO_BLOCK3]->position.z);
	RenderMesh(meshList[GEO_BLOCK3], meshList[GEO_BLOCK3]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK4]->position.x, meshList[GEO_BLOCK4]->position.y, meshList[GEO_BLOCK4]->position.z);
	RenderMesh(meshList[GEO_BLOCK4], meshList[GEO_BLOCK2]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK5]->position.x, meshList[GEO_BLOCK5]->position.y, meshList[GEO_BLOCK5]->position.z);
	RenderMesh(meshList[GEO_BLOCK5], meshList[GEO_BLOCK5]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK6]->position.x, meshList[GEO_BLOCK6]->position.y, meshList[GEO_BLOCK6]->position.z);
	RenderMesh(meshList[GEO_BLOCK6], meshList[GEO_BLOCK6]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK7]->position.x, meshList[GEO_BLOCK7]->position.y, meshList[GEO_BLOCK7]->position.z);
	RenderMesh(meshList[GEO_BLOCK7], meshList[GEO_BLOCK7]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK8]->position.x, meshList[GEO_BLOCK8]->position.y, meshList[GEO_BLOCK8]->position.z);
	RenderMesh(meshList[GEO_BLOCK8], meshList[GEO_BLOCK8]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK9]->position.x, meshList[GEO_BLOCK9]->position.y, meshList[GEO_BLOCK9]->position.z);
	RenderMesh(meshList[GEO_BLOCK9], meshList[GEO_BLOCK9]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BLOCK10]->position.x, meshList[GEO_BLOCK10]->position.y, meshList[GEO_BLOCK10]->position.z);
	RenderMesh(meshList[GEO_BLOCK10], meshList[GEO_BLOCK10]->light);
	modelStack.PopMatrix();

	

	//Wall(Thin)
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THIN1]->position.x, meshList[GEO_THIN1]->position.y, meshList[GEO_THIN1]->position.z);
	RenderMesh(meshList[GEO_THIN1], meshList[GEO_THIN1]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THIN2]->position.x, meshList[GEO_THIN2]->position.y, meshList[GEO_THIN2]->position.z);
	RenderMesh(meshList[GEO_THIN2], meshList[GEO_THIN2]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THIN3]->position.x, meshList[GEO_THIN3]->position.y, meshList[GEO_THIN3]->position.z);
	RenderMesh(meshList[GEO_THIN3], meshList[GEO_THIN3]->light);
	modelStack.PopMatrix();

	//Wall(Thin)2
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz1]->position.x, meshList[GEO_THINz1]->position.y, meshList[GEO_THINz1]->position.z);
	RenderMesh(meshList[GEO_THINz1], meshList[GEO_THINz1]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz2]->position.x, meshList[GEO_THINz2]->position.y, meshList[GEO_THINz2]->position.z);
	RenderMesh(meshList[GEO_THINz2], meshList[GEO_THINz2]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz3]->position.x, meshList[GEO_THINz3]->position.y, meshList[GEO_THINz3]->position.z);
	RenderMesh(meshList[GEO_THINz3], meshList[GEO_THINz3]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz4]->position.x, meshList[GEO_THINz4]->position.y, meshList[GEO_THINz4]->position.z);
	RenderMesh(meshList[GEO_THINz4], meshList[GEO_THINz4]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz5]->position.x, meshList[GEO_THINz5]->position.y, meshList[GEO_THINz5]->position.z);
	RenderMesh(meshList[GEO_THINz5], meshList[GEO_THINz5]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz6]->position.x, meshList[GEO_THINz6]->position.y, meshList[GEO_THINz6]->position.z);
	RenderMesh(meshList[GEO_THINz6], meshList[GEO_THINz6]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz7]->position.x, meshList[GEO_THINz7]->position.y, meshList[GEO_THINz7]->position.z);
	RenderMesh(meshList[GEO_THINz7], meshList[GEO_THINz7]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz8]->position.x, meshList[GEO_THINz8]->position.y, meshList[GEO_THINz8]->position.z);
	RenderMesh(meshList[GEO_THINz8], meshList[GEO_THINz8]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THINz9]->position.x, meshList[GEO_THINz9]->position.y, meshList[GEO_THINz9]->position.z);
	RenderMesh(meshList[GEO_THINz9], meshList[GEO_THINz9]->light);
	modelStack.PopMatrix();

	//Wall(Thick)
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THICK1]->position.x, meshList[GEO_THICK1]->position.y, meshList[GEO_THICK1]->position.z);
	RenderMesh(meshList[GEO_THICK1], meshList[GEO_THICK1]->light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_THICK2]->position.x, meshList[GEO_THICK2]->position.y, meshList[GEO_THICK2]->position.z);
	RenderMesh(meshList[GEO_THICK2], meshList[GEO_THICK2]->light);
	modelStack.PopMatrix();

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (fuel >20)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL1], 4, 7, 25, 4.8);
		modelStack.PopMatrix();
	}
	
	if (fuel > 40)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL2], 4, 7, 30, 4.8);
		modelStack.PopMatrix();
	}
	
		if (fuel > 60)
		{


			modelStack.PushMatrix();
			RenderOBJonScreen(meshList[GEO_FUEL3], 4, 7, 35, 4.8);
			modelStack.PopMatrix();
		}
	
	if (fuel>80)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL4], 4, 7, 40, 4.8);
		modelStack.PopMatrix();
		
	}
		
	
	if (fuel ==100)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL5], 4, 7, 45, 4.8);
		modelStack.PopMatrix();
	}
	if (object &&objectDied==false)
	{
		std::ostringstream enemyHp;
		//emyHp << std::setprecision(3) << bullets[0t].object->health;
		RenderTextOnScreen(meshList[GEO_ENEMYHEALTHDISPLAY], "Enemy HP: ", Color(0, 1, 0), 2, 25, 10);
	RenderTextOnScreen(meshList[GEO_ENEMYHEALTHDISPLAY],enemyHp.str(), Color(1, 1, 1), 2, 37, 10);
	}
	RenderTextOnScreen(meshList[GEO_JETPACKUI], jetfuelDisplay, Color(0, 1, 0), 2, 2, 2);
	RenderTextOnScreen(meshList[GEO_TIMEDISPLAY], timeDisplay, Color(0, 1, 0), 2, 2, 12);
	std::ostringstream timeString;
	timeString << std::setprecision(3) << time;
	RenderTextOnScreen(meshList[GEO_TIMEDISPLAY], timeString.str(), Color(0, 1, 0), 2, 8, 12);
}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
