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

void SP2::Scenario2Init()
{
	//Arena GROUND
	meshList[GEO_GROUND] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaFloor.obj");
	meshList[GEO_GROUND]->position.Set(0, -500, 0);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//sand.tga");

	//ArenaWalls
	meshList[GEO_ARENAWALLFRONT] = MeshBuilder::GenerateOBJ("arenawallfront", "OBJ//ArenaWallFrontBack.obj");
	meshList[GEO_ARENAWALLFRONT]->position.Set(0, -475, 250);

	meshList[GEO_ARENAWALLBACK] = MeshBuilder::GenerateOBJ("arenawallback", "OBJ//ArenaWallFrontBack.obj");
	meshList[GEO_ARENAWALLBACK]->position.Set(0, -475, -250);

	meshList[GEO_ARENAWALLLEFT] = MeshBuilder::GenerateOBJ("arenawallleft", "OBJ//ArenaWallLeftRight.obj");
	meshList[GEO_ARENAWALLLEFT]->position.Set(250, -475, 0);

	meshList[GEO_ARENAWALLRIGHT] = MeshBuilder::GenerateOBJ("arenawallright", "OBJ//ArenaWallLeftRight.obj");
	meshList[GEO_ARENAWALLRIGHT]->position.Set(-250, -475, 0);

	//Barrels
	meshList[GEO_BARREL1] = MeshBuilder::GenerateOBJ("arenabarrels", "OBJ//Barrel.obj");
	meshList[GEO_BARREL1]->position.Set(0, -490, 100);
	meshList[GEO_BARREL2] = MeshBuilder::GenerateOBJ("arenabarrels", "OBJ//Barrel.obj");
	meshList[GEO_BARREL2]->position.Set(0, -490, -100);
	meshList[GEO_BARREL3] = MeshBuilder::GenerateOBJ("arenabarrels", "OBJ//Barrel.obj");
	meshList[GEO_BARREL3]->position.Set(-100, -490, 0);
	meshList[GEO_BARREL4] = MeshBuilder::GenerateOBJ("arenabarrels", "OBJ//Barrel.obj");
	meshList[GEO_BARREL4]->position.Set(100, -490, 0);

	//Crates
	meshList[GEO_CRATE1] = MeshBuilder::GenerateOBJ("arenacrates", "OBJ//Crate.obj");
	meshList[GEO_CRATE1]->position.Set(0, -490, -200);
	meshList[GEO_CRATE2] = MeshBuilder::GenerateOBJ("arenacrates", "OBJ//Crate.obj");
	meshList[GEO_CRATE2]->position.Set(0, -490, 200);
	meshList[GEO_CRATE3] = MeshBuilder::GenerateOBJ("arenacrates", "OBJ//Crate.obj");
	meshList[GEO_CRATE3]->position.Set(-200, -490, 0);
	meshList[GEO_CRATE4] = MeshBuilder::GenerateOBJ("arenacrates", "OBJ//Crate.obj");
	meshList[GEO_CRATE4]->position.Set(200, -490, 0);

	//SqPyramids
	meshList[GEO_SQPYRA1] = MeshBuilder::GenerateOBJ("arenapyramid", "OBJ//SqPyramid.obj");
	meshList[GEO_SQPYRA1]->position.Set(-150, -490, -150);
	meshList[GEO_SQPYRA2] = MeshBuilder::GenerateOBJ("arenapyramid", "OBJ//SqPyramid.obj");
	meshList[GEO_SQPYRA2]->position.Set(150, -490, 150);

	//RdPyramids
	meshList[GEO_RDPYRA1] = MeshBuilder::GenerateOBJ("arenapyramid", "OBJ//RdPyramid.obj");
	meshList[GEO_RDPYRA1]->position.Set(-100, -490, 100);
	meshList[GEO_RDPYRA2] = MeshBuilder::GenerateOBJ("arenapyramid", "OBJ//RdPyramid.obj");
	meshList[GEO_RDPYRA2]->position.Set(100, -490, -100);

}
void SP2::Scenario3Init()
{
	

	//Arun's Wall
	//meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");
	meshList[GEO_FUEL1] = MeshBuilder::GenerateQuad("fuel1", Color(0.8, 0, 0));
	meshList[GEO_FUEL2] = MeshBuilder::GenerateQuad("fuel2", Color(1, 0, 0));
	meshList[GEO_FUEL3] = MeshBuilder::GenerateQuad("fuel3", Color(0, 0.8, 0));
	meshList[GEO_FUEL4] = MeshBuilder::GenerateQuad("fuel4", Color(0, 1, 0));
	meshList[GEO_FUEL5] = MeshBuilder::GenerateQuad("fuel5", Color(0.2, 1, 0.2));
	meshList[GEO_JETPACKUI] = MeshBuilder::GenerateQuad("Jetpack UI", Color(1, 2, 1));


	//LongWall
	meshList[GEO_LONGWALL] = MeshBuilder::GenerateOBJ("LongWall", "OBJ//LongWall.obj");
	meshList[GEO_LONGWALL]->position.Set(0, 20, -10);
	meshList[GEO_LONGWALL]->textureID = LoadTGA("Image//wallUI.tga");

	//Floor1
	meshList[GEO_FLOOR1] = MeshBuilder::GenerateOBJ("Floor1", "OBJ//Floor1.obj");
	meshList[GEO_FLOOR1]->position.Set(17, 0, -235);
	meshList[GEO_FLOOR1]->textureID = LoadTGA("Image//floor.tga");

	//Floor2
	meshList[GEO_FLOOR2] = MeshBuilder::GenerateOBJ("Floor2", "OBJ//Floor2.obj");
	meshList[GEO_FLOOR2]->position.Set(17, 0, -130);
	meshList[GEO_FLOOR2]->textureID = LoadTGA("Image//floor.tga");

	//Crate1
	meshList[GEO_CRATES1] = MeshBuilder::GenerateOBJ("crates", "OBJ//Crate.obj");
	meshList[GEO_CRATES1]->position.Set(11, 5, -150);
	meshList[GEO_CRATES1]->textureID = LoadTGA("Image//Crate.tga");

	//Crate2
	meshList[GEO_CRATES2] = MeshBuilder::GenerateOBJ("crates", "OBJ//Crate.obj");
	meshList[GEO_CRATES2]->position.Set(25, 5, -130);
	meshList[GEO_CRATES2]->textureID = LoadTGA("Image//Crate.tga");

	//Crate3
	meshList[GEO_CRATES3] = MeshBuilder::GenerateOBJ("crates", "OBJ//Crate.obj");
	meshList[GEO_CRATES3]->position.Set(11, 5, -110);
	meshList[GEO_CRATES3]->textureID = LoadTGA("Image//Crate.tga");

	//Balancewall1
	meshList[GEO_BALANCE1] = MeshBuilder::GenerateOBJ("balancewall", "OBJ//BalanceWall.obj");
	meshList[GEO_BALANCE1]->position.Set(17, 10, -50);
	meshList[GEO_BALANCE1]->textureID = LoadTGA("Image//scifiwall.tga");

	//Balancewall2
	meshList[GEO_BALANCE2] = MeshBuilder::GenerateOBJ("balancewall", "OBJ//BalanceWall.obj");
	meshList[GEO_BALANCE2]->position.Set(-17, 10, -80);
	meshList[GEO_BALANCE2]->textureID = LoadTGA("Image//scifiwall.tga");

	//Balancewall3
	meshList[GEO_BALANCE3] = MeshBuilder::GenerateOBJ("balancewall", "OBJ//BalanceWall.obj");
	meshList[GEO_BALANCE3]->position.Set(-17, 10, -120);
	meshList[GEO_BALANCE3]->textureID = LoadTGA("Image//scifiwall.tga");

	//Floor3
	meshList[GEO_FLOOR3] = MeshBuilder::GenerateOBJ("Floor3", "OBJ//Floor3.obj");
	meshList[GEO_FLOOR3]->position.Set(17, 0, 0);
	meshList[GEO_FLOOR3]->textureID = LoadTGA("Image//floor.tga");

	//WallRun1
	meshList[GEO_WALLRUN1] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN1]->position.Set(35, 20, 40);
	meshList[GEO_WALLRUN1]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun2
	meshList[GEO_WALLRUN2] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN2]->position.Set(5, 20, 75);
	meshList[GEO_WALLRUN2]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun3
	meshList[GEO_WALLRUN3] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN3]->position.Set(35, 20, 110);
	meshList[GEO_WALLRUN3]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun4
	meshList[GEO_WALLRUN4] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN4]->position.Set(-35, 20, 70);
	meshList[GEO_WALLRUN4]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun5
	meshList[GEO_WALLRUN5] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN5]->position.Set(-17.5, 20, 40);
	meshList[GEO_WALLRUN5]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun6
	meshList[GEO_WALLRUN6] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//WallRun.obj");
	meshList[GEO_WALLRUN6]->position.Set(-35, 20, 10);
	meshList[GEO_WALLRUN6]->textureID = LoadTGA("Image//wallUI.tga");

	//Floor4
	meshList[GEO_FLOOR4] = MeshBuilder::GenerateOBJ("Floor3", "OBJ//Floor4.obj");
	meshList[GEO_FLOOR4]->position.Set(17, 0, 195);
	meshList[GEO_FLOOR4]->textureID = LoadTGA("Image//floor.tga");

	//TallWall1
	meshList[GEO_TALLWALL1] = MeshBuilder::GenerateOBJ("tallwall", "OBJ//TallWall.obj");
	meshList[GEO_TALLWALL1]->position.Set(10, 20, 160);
	meshList[GEO_TALLWALL1]->textureID = LoadTGA("Image//scifiwall.tga");

	//TallWall2
	meshList[GEO_TALLWALL2] = MeshBuilder::GenerateOBJ("tallwall", "OBJ//TallWall.obj");
	meshList[GEO_TALLWALL2]->position.Set(25, 20, 175);
	meshList[GEO_TALLWALL2]->textureID = LoadTGA("Image//scifiwall.tga");

	//TallWall3
	meshList[GEO_TALLWALL3] = MeshBuilder::GenerateOBJ("tallwall", "OBJ//TallWall.obj");
	meshList[GEO_TALLWALL3]->position.Set(10, 20, 190);
	meshList[GEO_TALLWALL3]->textureID = LoadTGA("Image//scifiwall.tga");

	//TallCrate
	meshList[GEO_TALLCRATE] = MeshBuilder::GenerateOBJ("tallcrates", "OBJ//TallCrate.obj");
	meshList[GEO_TALLCRATE]->position.Set(30, 15, 210);
	meshList[GEO_TALLCRATE]->textureID = LoadTGA("Image//Crate.tga");

	//Floor5
	meshList[GEO_FLOOR5] = MeshBuilder::GenerateOBJ("Floor5", "OBJ//Floor5.obj");
	meshList[GEO_FLOOR5]->position.Set(-17, 0, 240);
	meshList[GEO_FLOOR5]->textureID = LoadTGA("Image//floor.tga");

	//Floor6
	meshList[GEO_FLOOR6] = MeshBuilder::GenerateOBJ("Floor6", "OBJ//Floor6.obj");
	meshList[GEO_FLOOR6]->position.Set(-17, 0, 140);
	meshList[GEO_FLOOR6]->textureID = LoadTGA("Image//floor.tga");

	//Floor7
	meshList[GEO_FLOOR7] = MeshBuilder::GenerateOBJ("Floor7", "OBJ//Floor7.obj");
	meshList[GEO_FLOOR7]->position.Set(-17, 0, -30);
	meshList[GEO_FLOOR7]->textureID = LoadTGA("Image//floor.tga");

	//Floor8
	meshList[GEO_FLOOR8] = MeshBuilder::GenerateOBJ("Floor8", "OBJ//Floor8.obj");
	meshList[GEO_FLOOR8]->position.Set(-17, 0, -200);
	meshList[GEO_FLOOR8]->textureID = LoadTGA("Image//floor.tga");

	//WallRun6
	meshList[GEO_WALLWALL1] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//Wallwall.obj");
	meshList[GEO_WALLWALL1]->position.Set(-20, 20, -200);
	meshList[GEO_WALLWALL1]->textureID = LoadTGA("Image//wallUI.tga");

	//WallRun6
	meshList[GEO_WALLWALL2] = MeshBuilder::GenerateOBJ("WallRUn", "OBJ//Wallwall.obj");
	meshList[GEO_WALLWALL2]->position.Set(-10, 20, -200);
	meshList[GEO_WALLWALL2]->textureID = LoadTGA("Image//wallUI.tga");


	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");

	meshList[GEO_MODEL1]->position.Set(10, 0, 10);
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//wallleft.tga");
	meshList[GEO_MODEL1]->interactable = true;

	//Map(FreeRun)

	

	//Turrets
	meshList[GEO_TURRET1] = MeshBuilder::GenerateOBJ("Turret", "OBJ//Turret.obj");
	meshList[GEO_TURRET1]->position.Set(60, 5, -480);
	meshList[GEO_TURRET1]->interactable = true;

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
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
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
	camera.Init(Vector3(0, 1000, -497), Vector3(0, 0, 0), Vector3(0, 1, 0));

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
	meshList[GEO_BULLET] = MeshBuilder::GenerateCube("bullet", Color(1, 1, 1));


	//Generate All Required Meshes
	Scenario2Init();
	Scenario3Init();
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text",16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_FLASH] = MeshBuilder::GenerateQuad("flash",Color(0,0,0));
	meshList[GEO_FLASH]->textureID = LoadTGA("Image//flash.tga");

	//UI
	meshList[GEO_HELMET] = MeshBuilder::GenerateQuad("UI", Color(0,0,0));
	meshList[GEO_HELMET]->textureID = LoadTGA("Image//helmetFinal.tga");

	//Crosshair
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("Crosshair", Color(0, 0, 0));
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//crosshair.tga");

	// Enable blendings
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//meshList[GEO_ALIEN_HEAD] = MeshBuilder::GenerateOBJ("Alien Head", "OBJ//Head.obj");
	//meshList[GEO_ALIEN_HEAD]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_HEAD]->position = Vector3(0, 0, -480);
	//meshList[GEO_ALIEN_BODY] = MeshBuilder::GenerateOBJ("Alien Body", "OBJ//Body.obj");
	//meshList[GEO_ALIEN_BODY]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_BODY]->position = Vector3(0, 0, -480);
	//meshList[GEO_ALIEN_HANDR] = MeshBuilder::GenerateOBJ("Alien Right Hand", "OBJ//RightHand.obj");
	//meshList[GEO_ALIEN_HANDR]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_HANDR]->position = Vector3(0, 0, -480);
	//meshList[GEO_ALIEN_HANDL] = MeshBuilder::GenerateOBJ("Alien Left Hand", "OBJ//LeftHand.obj");
	//meshList[GEO_ALIEN_HANDL]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_HANDL]->position = Vector3(0, 0, -480);
	//meshList[GEO_ALIEN_LEGR] = MeshBuilder::GenerateOBJ("Alien Right Leg", "OBJ//RightLeg.obj");
	//meshList[GEO_ALIEN_LEGR]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_LEGR]->position = Vector3(0, 0, -480);
	//meshList[GEO_ALIEN_LEGL] = MeshBuilder::GenerateOBJ("Alien Left Leg", "OBJ//LeftLeg.obj");
	//meshList[GEO_ALIEN_LEGL]->textureID = LoadTGA("Image//alienUV.tga");
	//meshList[GEO_ALIEN_LEGL]->position = Vector3(0, 0, -480);

	//alien.m_Head = meshList[GEO_ALIEN_HEAD];
	//alien.m_Body = meshList[GEO_ALIEN_BODY];
	//alien.m_HandL = meshList[GEO_ALIEN_HANDL];
	//alien.m_HandR = meshList[GEO_ALIEN_HANDR];
	//alien.m_LegL = meshList[GEO_ALIEN_LEGL];
	//alien.m_LegR = meshList[GEO_ALIEN_LEGR];
	//alien.move(alien.m_Body->position, camera.position, camera, meshList, GEO_LEFTWALL1, GEO_TEXT, time);
	//alien.transparency = 1;
//	temp.health = 100;
	meshList[GEO_ENEMY] = MeshBuilder::GenerateOBJ("apple", "OBJ//Rifle.obj");
	meshList[GEO_ENEMY]->textureID = LoadTGA("Image//Rifle .tga");

	meshList[GEO_PISTOL] = MeshBuilder::GenerateOBJ("apple", "OBJ//Pistol.obj");
	meshList[GEO_PISTOL]->textureID = LoadTGA("Image//Pistol.tga");
	meshList[GEO_SMG] = MeshBuilder::GenerateOBJ("apple", "OBJ//SMG.obj");
	meshList[GEO_SMG]->textureID = LoadTGA("Image//SMG.tga");
	meshList[GEO_STORE] = MeshBuilder::GenerateOBJ("apple", "OBJ//Store.obj");
	meshList[GEO_STORE]->textureID = LoadTGA("Image//Store.tga");
	meshList[GEO_STORE]->position = (0,0,0);
	player.inv.Rifle.delayMultiplier = 0.3;
	player.inv.Rifle.semiAuto = false;
	player.inv.Rifle.stopFiring = false;
	player.inv.GunSelected = &player.inv.Rifle;
	shoot.GunFiring = true;
	glUniform1f(m_parameters[U_MATERIAL_TRANSPARENCY], 1);
	meshList[GEO_RIFLE] = MeshBuilder::GenerateOBJ("Rifle", "OBJ//Rifle.obj");
//	meshList[GEO_THICK2]->position.Set(0, 3, -50);
	meshList[GEO_RIFLE]->textureID = LoadTGA("Image//Rifle.tga");
}

void SP2::Update(double dt)
{
	
	
	player.currentItems(dt, camera, meshList, player.object);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	
	time += dt;
	fps = 1 / dt;
	move.MovementCharac(dt, camera, meshList, GEO_LONGWALL, GEO_TEXT);
	camera.Update(dt);
	Vector3 bulletSpeed = (0.1, 0.1, 0.1);
	shoot.ShootingBullets(camera, dt, time, meshList,player);
	shoot.bulletHitDetection(mobs, dt, camera);
	//alien.move(alien.m_Body->position, camera.position, camera, meshList, GEO_LEFTWALL1, GEO_TEXT, time);
	object = shoot.Shootable(dt, camera, meshList,mobs);

	//Player Take Damage
	if (Application::IsKeyPressed('Z') && takeDamage == false)
	{
		takeDamage = true;
	}
	if (takeDamage == true && scaleHealth > 0)
	{
		scaleHealth -= dt;
	}
	if (Application::IsKeyPressed(VK_NUMPAD8))
	{
		pivot.y += dt;
	}
	if (Application::IsKeyPressed(VK_NUMPAD5))
	{
		pivot.y -= dt;
	}
	if (Application::IsKeyPressed(VK_NUMPAD4))
	{
		pivot.x += dt;
	}
	if (Application::IsKeyPressed(VK_NUMPAD6))
	{
		pivot.x -= dt;
	}
}

Mesh* SP2::Interaction(double dt)
{
	float range = 20;
	float offset = 0.5;

	for (Vector3 temp = camera.view.Normalized(); temp.Length() <= range ; temp += camera.view.Normalized())
	{
		for (int i = GEO_LONGWALL; i < GEO_TEXT; i++)

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

void SP2::RenderMesh(Mesh * mesh, bool enableLight, MS ms, MS vs, MS ps)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = ps.Top() * vs.Top() * ms.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = vs.Top() * ms.Top();
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
	float SkyScale = 1000.f;
	float offset = 1;

	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);

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
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, SkyScale / 2 - offset, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(SkyScale, SkyScale, SkyScale);
	RenderMesh(meshList[GEO_LEFT], false);
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
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
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
	if (mesh == meshList[GEO_UIBG])
	{
		modelStack.Rotate(180, 0, 0, 1);
	}
	modelStack.Scale(sizex, sizey, 1);
	modelStack.Rotate(90, 1, 0, 0);
	if (mesh == meshList[GEO_RIFLE])
	{
		modelStack.Rotate(-85, 1, 0, 0);
		modelStack.Rotate(195, 0, 1, 0);
		modelStack.Translate(-10, -10, 60);
	}
	if (mesh == meshList[GEO_PISTOL])
	{
		modelStack.Scale(2, 2, 2);
		modelStack.Rotate(-85, 1, 0, 0);
		modelStack.Rotate(105, 0, 1, 0);
		modelStack.Translate(10, -5,0);
	}
	if (mesh == meshList[GEO_SMG])
	{
		modelStack.Scale(9, 9, 9);
		modelStack.Rotate(-85, 1, 0, 0);
		modelStack.Rotate(195, 0, 1, 0);
		modelStack.Translate(-2, -5.5,10);
	}
	if (mesh == meshList[GEO_HELMET])
	{
		modelStack.Translate(0, 0.1, 0);
		modelStack.Rotate(-90, 0, 1, 0);
	}
	
	
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

void SP2::Scenario2Render()
{
	//Ground
	modelStack.PushMatrix();
	//modelStack.Scale(500, 500, 500);
	modelStack.Translate(meshList[GEO_GROUND]->position.x, meshList[GEO_GROUND]->position.y, meshList[GEO_GROUND]->position.z);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	//ArenaWalls
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENAWALLFRONT]->position.x, meshList[GEO_ARENAWALLFRONT]->position.y, meshList[GEO_ARENAWALLFRONT]->position.z);
	RenderMesh(meshList[GEO_ARENAWALLFRONT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENAWALLBACK]->position.x, meshList[GEO_ARENAWALLBACK]->position.y, meshList[GEO_ARENAWALLBACK]->position.z);
	RenderMesh(meshList[GEO_ARENAWALLBACK], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENAWALLLEFT]->position.x, meshList[GEO_ARENAWALLLEFT]->position.y, meshList[GEO_ARENAWALLLEFT]->position.z);
	RenderMesh(meshList[GEO_ARENAWALLLEFT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENAWALLRIGHT]->position.x, meshList[GEO_ARENAWALLRIGHT]->position.y, meshList[GEO_ARENAWALLRIGHT]->position.z);
	RenderMesh(meshList[GEO_ARENAWALLRIGHT], true);
	modelStack.PopMatrix();

	//Barrels
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BARREL1]->position.x, meshList[GEO_BARREL1]->position.y, meshList[GEO_BARREL1]->position.z);
	RenderMesh(meshList[GEO_BARREL1], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BARREL2]->position.x, meshList[GEO_BARREL2]->position.y, meshList[GEO_BARREL2]->position.z);
	RenderMesh(meshList[GEO_BARREL2], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BARREL3]->position.x, meshList[GEO_BARREL3]->position.y, meshList[GEO_BARREL3]->position.z);
	RenderMesh(meshList[GEO_BARREL3], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BARREL4]->position.x, meshList[GEO_BARREL4]->position.y, meshList[GEO_BARREL4]->position.z);
	RenderMesh(meshList[GEO_BARREL4], true);
	modelStack.PopMatrix();
	

	//Crates
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATE1]->position.x, meshList[GEO_CRATE1]->position.y, meshList[GEO_CRATE1]->position.z);
	RenderMesh(meshList[GEO_CRATE1], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATE2]->position.x, meshList[GEO_CRATE2]->position.y, meshList[GEO_CRATE2]->position.z);
	RenderMesh(meshList[GEO_CRATE2], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATE3]->position.x, meshList[GEO_CRATE3]->position.y, meshList[GEO_CRATE3]->position.z);
	RenderMesh(meshList[GEO_CRATE3], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATE4]->position.x, meshList[GEO_CRATE4]->position.y, meshList[GEO_CRATE4]->position.z);
	RenderMesh(meshList[GEO_CRATE4], true);
	modelStack.PopMatrix();

	//SqPyramids
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_SQPYRA1]->position.x, meshList[GEO_SQPYRA1]->position.y, meshList[GEO_SQPYRA1]->position.z);
	RenderMesh(meshList[GEO_SQPYRA1], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_SQPYRA2]->position.x, meshList[GEO_SQPYRA2]->position.y, meshList[GEO_SQPYRA2]->position.z);
	RenderMesh(meshList[GEO_SQPYRA2], true);
	modelStack.PopMatrix();

	//RdPyramids
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RDPYRA1]->position.x, meshList[GEO_RDPYRA1]->position.y, meshList[GEO_RDPYRA1]->position.z);
	RenderMesh(meshList[GEO_RDPYRA1], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RDPYRA2]->position.x, meshList[GEO_RDPYRA2]->position.y, meshList[GEO_RDPYRA2]->position.z);
	RenderMesh(meshList[GEO_RDPYRA2], true);
	modelStack.PopMatrix();

}

void SP2::Scenario3Render()
{

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LONGWALL]->position.x, meshList[GEO_LONGWALL]->position.y, meshList[GEO_LONGWALL]->position.z);
	RenderMesh(meshList[GEO_LONGWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR1]->position.x, meshList[GEO_FLOOR1]->position.y, meshList[GEO_FLOOR1]->position.z);
	RenderMesh(meshList[GEO_FLOOR1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR2]->position.x, meshList[GEO_FLOOR2]->position.y, meshList[GEO_FLOOR2]->position.z);
	RenderMesh(meshList[GEO_FLOOR2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATES1]->position.x, meshList[GEO_CRATES1]->position.y, meshList[GEO_CRATES1]->position.z);
	RenderMesh(meshList[GEO_CRATES1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATES2]->position.x, meshList[GEO_CRATES2]->position.y, meshList[GEO_CRATES2]->position.z);
	RenderMesh(meshList[GEO_CRATES2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_CRATES3]->position.x, meshList[GEO_CRATES3]->position.y, meshList[GEO_CRATES3]->position.z);
	RenderMesh(meshList[GEO_CRATES3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BALANCE1]->position.x, meshList[GEO_BALANCE1]->position.y, meshList[GEO_BALANCE1]->position.z);
	RenderMesh(meshList[GEO_BALANCE1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BALANCE2]->position.x, meshList[GEO_BALANCE2]->position.y, meshList[GEO_BALANCE2]->position.z);
	RenderMesh(meshList[GEO_BALANCE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BALANCE3]->position.x, meshList[GEO_BALANCE3]->position.y, meshList[GEO_BALANCE3]->position.z);
	RenderMesh(meshList[GEO_BALANCE3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR3]->position.x, meshList[GEO_FLOOR3]->position.y, meshList[GEO_FLOOR3]->position.z);
	RenderMesh(meshList[GEO_FLOOR3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN1]->position.x, meshList[GEO_WALLRUN1]->position.y, meshList[GEO_WALLRUN1]->position.z);
	RenderMesh(meshList[GEO_WALLRUN1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN2]->position.x, meshList[GEO_WALLRUN2]->position.y, meshList[GEO_WALLRUN2]->position.z);
	RenderMesh(meshList[GEO_WALLRUN2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN3]->position.x, meshList[GEO_WALLRUN3]->position.y, meshList[GEO_WALLRUN3]->position.z);
	RenderMesh(meshList[GEO_WALLRUN3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN4]->position.x, meshList[GEO_WALLRUN4]->position.y, meshList[GEO_WALLRUN4]->position.z);
	RenderMesh(meshList[GEO_WALLRUN4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN5]->position.x, meshList[GEO_WALLRUN5]->position.y, meshList[GEO_WALLRUN5]->position.z);
	RenderMesh(meshList[GEO_WALLRUN5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLRUN6]->position.x, meshList[GEO_WALLRUN6]->position.y, meshList[GEO_WALLRUN6]->position.z);
	RenderMesh(meshList[GEO_WALLRUN6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR4]->position.x, meshList[GEO_FLOOR4]->position.y, meshList[GEO_FLOOR4]->position.z);
	RenderMesh(meshList[GEO_FLOOR4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_TALLWALL1]->position.x, meshList[GEO_TALLWALL1]->position.y, meshList[GEO_TALLWALL1]->position.z);
	RenderMesh(meshList[GEO_TALLWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_TALLWALL2]->position.x, meshList[GEO_TALLWALL2]->position.y, meshList[GEO_TALLWALL2]->position.z);
	RenderMesh(meshList[GEO_TALLWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_TALLWALL3]->position.x, meshList[GEO_TALLWALL3]->position.y, meshList[GEO_TALLWALL3]->position.z);
	RenderMesh(meshList[GEO_TALLWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_TALLCRATE]->position.x, meshList[GEO_TALLCRATE]->position.y, meshList[GEO_TALLCRATE]->position.z);
	RenderMesh(meshList[GEO_TALLCRATE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR5]->position.x, meshList[GEO_FLOOR5]->position.y, meshList[GEO_FLOOR5]->position.z);
	RenderMesh(meshList[GEO_FLOOR5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR6]->position.x, meshList[GEO_FLOOR6]->position.y, meshList[GEO_FLOOR6]->position.z);
	RenderMesh(meshList[GEO_FLOOR6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR7]->position.x, meshList[GEO_FLOOR7]->position.y, meshList[GEO_FLOOR7]->position.z);
	RenderMesh(meshList[GEO_FLOOR7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FLOOR8]->position.x, meshList[GEO_FLOOR8]->position.y, meshList[GEO_FLOOR8]->position.z);
	RenderMesh(meshList[GEO_FLOOR8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLWALL1]->position.x, meshList[GEO_WALLWALL1]->position.y, meshList[GEO_WALLWALL1]->position.z);
	RenderMesh(meshList[GEO_WALLWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_WALLWALL2]->position.x, meshList[GEO_WALLWALL2]->position.y, meshList[GEO_WALLWALL2]->position.z);
	RenderMesh(meshList[GEO_WALLWALL2], true);
	modelStack.PopMatrix();

	

	//Turrets
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_TURRET1]->position.x, meshList[GEO_TURRET1]->position.y, meshList[GEO_TURRET1]->position.z);
	RenderMesh(meshList[GEO_TURRET1], meshList[GEO_TURRET1]->light);
	modelStack.PopMatrix();
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

	
		for (int a = 0; a <shoot.bullets.size(); a++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(shoot.bullets[a].Position.x, shoot.bullets[a].Position.y, shoot.bullets[a].Position.z);
			modelStack.Scale(0.1, 0.1,0.1);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}

	//Arun's Wall
	
	//Render Scenario2
	Scenario2Render();

	//Render Scenario3
	Scenario3Render();

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//////////////////////////////////
	//			Enemy Health        //
	/////////////////////////////////
	if (object )
	{
	//	cout << healthDisplay.health<<endl;
		if (object->ifShootable == true)
		{
			std::ostringstream enemyHp;
			enemyHp << std::setprecision(3) << object->health;
			RenderTextOnScreen(meshList[GEO_TEXT], "Enemy HP: ", Color(0, 1, 0), 2, 25, 10);
			RenderTextOnScreen(meshList[GEO_TEXT], enemyHp.str(), Color(1, 1, 1), 2, 37, 10);
			//		std::ostringstream enemyHp;
		}
	}
	
	//////////////////////////////////
	//			JetFuel             //
	/////////////////////////////////
	if (move.jetPack.getStatus() == false && (fmod(time, 0.2) < 0.1))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "DISABLED !!!", Color(1, 0, 0), 2, 2, 7);
	}
	if (move.jetPack.getFuel() > 15)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL1], 30, 1, 6, 4);
		modelStack.PopMatrix();
	}
	
	if (move.jetPack.getFuel() > 40)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL2], 25, 1, 8.5, 6);
		modelStack.PopMatrix();
	}
	
	if (move.jetPack.getFuel() > 60)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL3], 20, 1, 11, 8);
		modelStack.PopMatrix();
	}
	
	if (move.jetPack.getFuel() >80)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL4], 15, 1, 13.5, 10);
		modelStack.PopMatrix();
	}

	if (move.jetPack.getFuel() > 95)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_FUEL5], 20, 1, 11, 12);
		modelStack.PopMatrix();
	}


	//////////////////////////////////
	//			Time               //
	/////////////////////////////////
	
	RenderTextOnScreen(meshList[GEO_TEXT],"Time: ", Color(1, 0, 0), 2, 2, 25);
	std::ostringstream timeString;
	timeString << std::setprecision(3) << time;
	RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 3, 24);


	//////////////////////////////////
	//			Gun                //
	/////////////////////////////////
	//RenderTextOnScreen(meshList[GEO_TEXT], "Gun Mode: ", Color(0, 1, 0), 2, 30, 6);
	if (player.inv.GunSelected->semiAuto==false)
	{
		//RenderTextOnScreen(meshList[GEO_TEXT], "|||", Color(0, 1, 0), 3, 21 , 3);
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_GUNMODE], 1, 3, 61, 11);
		RenderOBJonScreen(meshList[GEO_GUNMODE], 1, 3, 63, 11);
		RenderOBJonScreen(meshList[GEO_GUNMODE], 1, 3, 65, 11);
		modelStack.PopMatrix();
	}
	else if (player.inv.GunSelected->semiAuto == true)
	{
		modelStack.PushMatrix();						   
		RenderOBJonScreen(meshList[GEO_GUNMODE], 1, 3, 61, 11); 
		modelStack.PopMatrix();
	}
	timeString.str("");
	timeString << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(0, 1, 0), 2, 8, 11);
	
	//UI Background Panal
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_UIBG], 25, 19, 72, 3.5);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_STORE]->position.x, meshList[GEO_STORE]->position.y, meshList[GEO_STORE]->position.z);
	RenderMesh(meshList[GEO_STORE], false);
	modelStack.PopMatrix();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Player's Health
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_PLAYERHEALTH], 30*scaleHealth, 1, 40, 55);
	modelStack.PopMatrix();

	//Crosshair
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_CROSSHAIR], 10, 10, 40.2, 29.8);
	modelStack.PopMatrix();


if (player.inv.GunSelected == &player.inv.Rifle)
	{
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_RIFLE], 0.8, 0.8, 70, 20);
		modelStack.PopMatrix();
	}
else if (player.inv.GunSelected == &player.inv.SMG)
{
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_SMG], 0.8, 0.8, 70, 20);
	modelStack.PopMatrix();
}
else if (player.inv.GunSelected = &player.inv.Pistol)
{
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_PISTOL], 0.8, 0.8, 70, 17);
	modelStack.PopMatrix();
}
	modelStack.PushMatrix();
	RenderOBJonScreen(meshList[GEO_HELMET], 80, 60, 40 , 30);
	modelStack.PopMatrix();
}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
