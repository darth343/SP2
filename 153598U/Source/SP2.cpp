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
#include <fstream>
#include <strstream>
#include <stdio.h>

using std::cout;
using std::endl;


SP2::SP2()
{
	state = MAIN_MENU;
}

SP2::~SP2()
{
}

void SP2::Init()
{
	move.allowInput = true;
	// Init VBO here
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(100, 100, 100);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.5;
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
	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(100, 100, 100);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	light[2].type = Light::LIGHT_DIRECTIONAL;
	light[2].position.Set(100, 100, 100);
	light[2].color.Set(1, 1, 1);
	light[2].power = 0;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(100, 100, 100);
	light[3].color.Set(1, 1, 1);
	light[3].power = 0;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(10));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(18, 15, -243), Vector3(0, 0, 0), Vector3(0, 1, 0));
	//camera.Init(Vector3(0, 270, -443), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
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
	ScenarioArenaInit();
	ScenarioParkourInit();
	ScenarioRunnerInit();
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text",16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//alienText.tga");

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

	meshList[GEO_FUEL1] = MeshBuilder::GenerateQuad("fuel1", Color(0.2, 0.2, 0.2));
	meshList[GEO_FUEL2] = MeshBuilder::GenerateQuad("fuel2", Color(0.4, 0.4, 0.4));
	meshList[GEO_FUEL3] = MeshBuilder::GenerateQuad("fuel3", Color(0.6, 0.6, 0.6));
	meshList[GEO_FUEL4] = MeshBuilder::GenerateQuad("fuel4", Color(0.8, 0.8, 0.8));
	meshList[GEO_FUEL5] = MeshBuilder::GenerateQuad("fuel5", Color(1, 1, 1));
	meshList[GEO_JETPACKUI] = MeshBuilder::GenerateQuad("Jetpack UI", Color(1, 2, 1));

	//MainMenu
	meshList[GEO_MAINMENU] = MeshBuilder::GenerateQuad("UI", Color(0, 0, 0));
	meshList[GEO_MAINMENU]->textureID = LoadTGA("Image//MainMenu.tga");
	meshList[GEO_MAINMENUBOX1] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 0, 0));
	meshList[GEO_MAINMENUBOX2] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 0, 0));

	Math::InitRNG();
	srand(Math::RandIntMinMax(0, 500));
	//Aliens
	vector<Vector3> coordinates = 
	{
		Vector3(110, -501, 55),
		Vector3(59, -501, 55),
		Vector3(84, -501, 152),
		Vector3(0, -501, 21),
		Vector3(12, -501, -160),
		Vector3(-160, -501, -39),
		Vector3(-170, -501, 18),
		Vector3(-130, -501, 162),
		Vector3(70, -501, 153),
		Vector3(95, -501, -33),
		Vector3(-26, -501, 172),
		Vector3(-136, -501, 6),
		Vector3(-169, -501, -152),
		Vector3(-14, -501, -150),
		Vector3(-74, -501, -71),
		Vector3(-110, -501, -61),
		Vector3(162, -501, 93),
	};

	int i = 0;
	while (i <= 9)
	{
		int slot = rand() % coordinates.size();
		AI temp;
		temp.m_Head = MeshBuilder::GenerateOBJ("Alien Head", "OBJ//Head.obj");
		temp.m_Head->textureID = LoadTGA("Image//alienUV.tga");
		temp.m_Body = MeshBuilder::GenerateOBJ("Alien Body", "OBJ//Body.obj");
		temp.m_Body->textureID = LoadTGA("Image//alienUV.tga");
		temp.m_HandR = MeshBuilder::GenerateOBJ("Alien Right Hand", "OBJ//RightHand.obj");
		temp.m_HandR->textureID = LoadTGA("Image//alienUV.tga");
		temp.m_HandL = MeshBuilder::GenerateOBJ("Alien Left Hand", "OBJ//LeftHand.obj");
		temp.m_HandL->textureID = LoadTGA("Image//alienUV.tga");
		temp.m_LegR = MeshBuilder::GenerateOBJ("Alien Right Leg", "OBJ//RightLeg.obj");
		temp.m_LegR->textureID = LoadTGA("Image//alienUV.tga");
		temp.m_LegL = MeshBuilder::GenerateOBJ("Alien Left Leg", "OBJ//LeftLeg.obj");
		temp.m_LegL->textureID = LoadTGA("Image//alienUV.tga");

		temp.transparency = 0.01;
		temp.position = coordinates[slot];
		coordinates.erase(coordinates.begin() + slot);
		++i;
		temp.temp = temp.position;
		allAliens.push_back(temp);
		cout << temp.position << endl;
	}

	//Player Health
	meshList[GEO_PLAYERHEALTH] = MeshBuilder::GenerateQuad("Player Health", Color(0.71, 0.03, 0.03));

	//UI Background
	meshList[GEO_UIBG] = MeshBuilder::GenerateQuad("UI Background Panal", Color(0.37, 0.37, 0.37));
	meshList[GEO_GUNMODE] = MeshBuilder::GenerateQuad("Gun Mode", Color(0.25, 0.25, 0.25));

	meshList[GEO_PISTOL] = MeshBuilder::GenerateOBJ("apple", "OBJ//Pistol.obj");
	meshList[GEO_PISTOL]->textureID = LoadTGA("Image//Pistol.tga");
	meshList[GEO_SMG] = MeshBuilder::GenerateOBJ("apple", "OBJ//SMG.obj");
	meshList[GEO_SMG]->textureID = LoadTGA("Image//SMG.tga");
	
	player.object = nullptr;
	player.inv.Rifle.delayMultiplier = 0.3;
	player.inv.Rifle.semiAuto = false;
	player.inv.Rifle.stopFiring = false;
	player.inv.GunSelected = &player.inv.Rifle;
	glUniform1f(m_parameters[U_MATERIAL_TRANSPARENCY], 1);
	meshList[GEO_RIFLE] = MeshBuilder::GenerateOBJ("Rifle", "OBJ//Rifle.obj");
	meshList[GEO_RIFLE]->textureID = LoadTGA("Image//Rifle.tga");
	meshList[GEO_BLACKSCREEN] = MeshBuilder::GenerateQuad("UI", Color(0, 0, 0));
	meshList[GEO_GAMEOVER] = MeshBuilder::GenerateQuad("UI", Color(0, 0, 0));
	meshList[GEO_GAMEOVER]->textureID = LoadTGA("Image//GameOver.tga");
	meshList[GEO_RUNNERSCREEN] = MeshBuilder::GenerateQuad("RUNSCREEN", Color(0, 0, 0));
	meshList[GEO_SHOPMENU] = MeshBuilder::GenerateQuad("Shop", Color(0, 0, 0));
	meshList[GEO_SHOPMENU]->textureID = LoadTGA("Image//ShopMenu.tga");
	coin.init();
	//TriggerBox temp(Vector3(-14, 260, -420), Vector3(14, 300, -390), "test");
	//events.push_back(temp);


	Start.mini = Vector3(462, 389, 0);
	Start.maxi = Vector3(942, 450, 0);

	Quit.mini = Vector3(462, 486, 0);
	Quit.maxi = Vector3(943, 547, 0);

	//Scenario 1 Ending Trigger Box
	TriggerBox temp(Vector3(-35, 10, -250), Vector3(-4, 50, -228), Vector3(160, -492, -250), "Your Ship is under Attack!", "Kill All Aliens", 3, 2.5, 2, 30, 20, 27);
	events.push_back(temp);
	//Scenario 2 Ending Trigger Box
	TriggerBox temp2(Vector3(-14, -500, -9), Vector3(12, -480, 17), Vector3(0, 260, -443), "Reinforcements Inbound for Extraction", "GET TO THE SHIPPAA", 2, 2, 4, 30, 20, 27);
	events.push_back(temp2);
	//Scenario 3 Ending Trigger Box
	TriggerBox temp3(Vector3(-15, 240, 413), Vector3(15, 310, 450), Vector3(0, 0, 0), "SWEET VICTORY! You made it back safely!", "(Congratulations on Winning!)", 2, 2, 4, 30, 20, 27);
	events.push_back(temp3);
	//Scenario 1 reset Trigger Box
	TriggerBox temp4(Vector3(-500, -40, -500), Vector3(500, -15, 500), Vector3(0, 0, 0), "", "", 2, 2, 4, 30, 20, 27);
	events.push_back(temp4);
	//Scenario 3 reset Trigger Box
	TriggerBox temp5(Vector3(-500, 230, -450), Vector3(500, 250, 450), Vector3(0, 260, -443), "", "", 2, 2, 4, 30, 20, 27);
	events.push_back(temp5);
	highscore.init();
}

void SP2::ScenarioArenaInit()
{
	//Arena GROUND
	meshList[GEO_GROUND] = MeshBuilder::GenerateOBJ("ground", "OBJ//Ground.obj");
	meshList[GEO_GROUND]->position.Set(0, -500, 0);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//ArenaWall.tga");
	meshList[GEO_ARENAFRONTWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaFrontWall1.obj");
	meshList[GEO_ARENAFRONTWALL1]->position.Set(0, -500, 0);
	meshList[GEO_ARENAFRONTWALL1]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_ARENAFRONTWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaFrontWall2.obj");
	meshList[GEO_ARENAFRONTWALL2]->position.Set(0, -500, 0);
	meshList[GEO_ARENAFRONTWALL2]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_ARENAFRONTWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaFrontWall3.obj");
	meshList[GEO_ARENAFRONTWALL3]->position.Set(0, -500, 0);
	meshList[GEO_ARENAFRONTWALL3]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_ARENALEFTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaLeftWall.obj");
	meshList[GEO_ARENALEFTWALL]->position.Set(0, -500, 0);
	meshList[GEO_ARENALEFTWALL]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_ARENARIGHTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaRightWall.obj");
	meshList[GEO_ARENARIGHTWALL]->position.Set(0, -500, 0);
	meshList[GEO_ARENARIGHTWALL]->textureID = LoadTGA("Image//Arena3rdMaze.tga");

	meshList[GEO_ARENABACKWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaBackWall1.obj");
	meshList[GEO_ARENABACKWALL1]->position.Set(0, -500, 0);
	meshList[GEO_ARENABACKWALL1]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_ARENABACKWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaBackWall2.obj");
	meshList[GEO_ARENABACKWALL2]->position.Set(0, -500, 0);
	meshList[GEO_ARENABACKWALL2]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_ARENABACKWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//ArenaBackWall3.obj");
	meshList[GEO_ARENABACKWALL3]->position.Set(0, -500, 0);
	meshList[GEO_ARENABACKWALL3]->textureID = LoadTGA("Image//Arena1stMaze.tga");

	meshList[GEO_LANDINGPAD1] = MeshBuilder::GenerateOBJ("ground", "OBJ//LandingPad.obj");
	meshList[GEO_LANDINGPAD1]->position.Set(0, -500, 0);
	meshList[GEO_LANDINGPAD1]->textureID = LoadTGA("Image//ArenaWall.tga");

	meshList[GEO_LANDINGPAD2] = MeshBuilder::GenerateOBJ("ground", "OBJ//LandingPad2.obj");
	meshList[GEO_LANDINGPAD2]->position.Set(0, -500, 0);
	meshList[GEO_LANDINGPAD2]->textureID = LoadTGA("Image//ArenaWall.tga");


	meshList[GEO_FRONTINTERSECTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//FrontIntersectWall.obj");
	meshList[GEO_FRONTINTERSECTWALL]->position.Set(0, -500, 0);
	meshList[GEO_FRONTINTERSECTWALL]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_BACKINTERSECTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//BackIntersectWall.obj");
	meshList[GEO_BACKINTERSECTWALL]->position.Set(0, -500, 0);
	meshList[GEO_BACKINTERSECTWALL]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_LEFTINTERSECTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//LeftIntersectWall.obj");
	meshList[GEO_LEFTINTERSECTWALL]->position.Set(0, -500, 0);
	meshList[GEO_LEFTINTERSECTWALL]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_RIGHTINTERSECTWALL] = MeshBuilder::GenerateOBJ("ground", "OBJ//RightIntersectWall.obj");
	meshList[GEO_RIGHTINTERSECTWALL]->position.Set(0, -500, 0);
	meshList[GEO_RIGHTINTERSECTWALL]->textureID = LoadTGA("Image//Arena2ndMaze.tga");

	meshList[GEO_MIDDLEPILLAR] = MeshBuilder::GenerateOBJ("ground", "OBJ//MiddlePillar.obj");
	meshList[GEO_MIDDLEPILLAR]->position.Set(0, -500, 0);
	meshList[GEO_MIDDLEPILLAR]->textureID = LoadTGA("Image//MiddlePillar.tga");

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("ground", "OBJ//Door.obj");
	meshList[GEO_DOOR]->position.Set(0, -500, 0);
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//ArenaWall.tga");

	meshList[GEO_1STMAZEWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall1.obj");
	meshList[GEO_1STMAZEWALL1]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL1]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall2.obj");
	meshList[GEO_1STMAZEWALL2]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL2]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall3.obj");
	meshList[GEO_1STMAZEWALL3]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL3]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL4] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall4.obj");
	meshList[GEO_1STMAZEWALL4]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL4]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL5] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall5.obj");
	meshList[GEO_1STMAZEWALL5]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL5]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL6] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall6.obj");
	meshList[GEO_1STMAZEWALL6]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL6]->textureID = LoadTGA("Image//Arena1stMaze.tga");
	meshList[GEO_1STMAZEWALL7] = MeshBuilder::GenerateOBJ("ground", "OBJ//1stMazeWall7.obj");
	meshList[GEO_1STMAZEWALL7]->position.Set(0, -500, 0);
	meshList[GEO_1STMAZEWALL7]->textureID = LoadTGA("Image//Arena1stMaze.tga");

	meshList[GEO_2NDMAZEWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall1.obj");
	meshList[GEO_2NDMAZEWALL1]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL1]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_2NDMAZEWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall2.obj");
	meshList[GEO_2NDMAZEWALL2]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL2]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_2NDMAZEWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall3.obj");
	meshList[GEO_2NDMAZEWALL3]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL3]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_2NDMAZEWALL4] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall4.obj");
	meshList[GEO_2NDMAZEWALL4]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL4]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_2NDMAZEWALL5] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall5.obj");
	meshList[GEO_2NDMAZEWALL5]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL5]->textureID = LoadTGA("Image//Arena2ndMaze.tga");
	meshList[GEO_2NDMAZEWALL6] = MeshBuilder::GenerateOBJ("ground", "OBJ//2ndMazeWall6.obj");
	meshList[GEO_2NDMAZEWALL6]->position.Set(0, -500, 0);
	meshList[GEO_2NDMAZEWALL6]->textureID = LoadTGA("Image//Arena2ndMaze.tga");

	meshList[GEO_3RDMAZEWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall1.obj");
	meshList[GEO_3RDMAZEWALL1]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL1]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall2.obj");
	meshList[GEO_3RDMAZEWALL2]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL2]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall3.obj");
	meshList[GEO_3RDMAZEWALL3]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL3]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL4] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall4.obj");
	meshList[GEO_3RDMAZEWALL4]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL4]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL5] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall5.obj");
	meshList[GEO_3RDMAZEWALL5]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL5]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL6] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall6.obj");
	meshList[GEO_3RDMAZEWALL6]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL6]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL7] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall7.obj");
	meshList[GEO_3RDMAZEWALL7]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL7]->textureID = LoadTGA("Image//Arena3rdMaze.tga");
	meshList[GEO_3RDMAZEWALL8] = MeshBuilder::GenerateOBJ("ground", "OBJ//3rdMazeWall7.obj");
	meshList[GEO_3RDMAZEWALL8]->position.Set(0, -500, 0);
	meshList[GEO_3RDMAZEWALL8]->textureID = LoadTGA("Image//Arena3rdMaze.tga");

	meshList[GEO_4THMAZEWALL1] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall1.obj");
	meshList[GEO_4THMAZEWALL1]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL1]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL2] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall2.obj");
	meshList[GEO_4THMAZEWALL2]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL2]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL3] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall3.obj");
	meshList[GEO_4THMAZEWALL3]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL3]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL4] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall4.obj");
	meshList[GEO_4THMAZEWALL4]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL4]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL5] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall5.obj");
	meshList[GEO_4THMAZEWALL5]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL5]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL6] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall6.obj");
	meshList[GEO_4THMAZEWALL6]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL6]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL7] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall7.obj");
	meshList[GEO_4THMAZEWALL7]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL7]->textureID = LoadTGA("Image//Arena4thMaze.tga");
	meshList[GEO_4THMAZEWALL8] = MeshBuilder::GenerateOBJ("ground", "OBJ//4thMazeWall7.obj");
	meshList[GEO_4THMAZEWALL8]->position.Set(0, -500, 0);
	meshList[GEO_4THMAZEWALL8]->textureID = LoadTGA("Image//Arena4thMaze.tga");


	meshList[GEO_STORE] = MeshBuilder::GenerateOBJ("store", "OBJ//Store.obj");
	meshList[GEO_STORE]->textureID = LoadTGA("Image//Store.tga");
	meshList[GEO_STORE]->position.Set(130, -500, -79);
}

void SP2::ScenarioParkourInit()
{
	meshList[GEO_FUEL1] = MeshBuilder::GenerateQuad("fuel1", Color(0.8, 0, 0));
	meshList[GEO_FUEL2] = MeshBuilder::GenerateQuad("fuel2", Color(1, 0, 0));
	meshList[GEO_FUEL3] = MeshBuilder::GenerateQuad("fuel3", Color(0, 0.8, 0));
	meshList[GEO_FUEL4] = MeshBuilder::GenerateQuad("fuel4", Color(0, 1, 0));
	meshList[GEO_FUEL5] = MeshBuilder::GenerateQuad("fuel5", Color(0.2, 1, 0.2));

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

	//BalanceWall1
	meshList[GEO_BALANCE1] = MeshBuilder::GenerateOBJ("BalanceWall", "OBJ//BalanceWall.obj");
	meshList[GEO_BALANCE1]->position.Set(17, 10, -50);
	meshList[GEO_BALANCE1]->textureID = LoadTGA("Image//scifiwall.tga");

	//BalanceWall2
	meshList[GEO_BALANCE2] = MeshBuilder::GenerateOBJ("BalanceWall", "OBJ//BalanceWall.obj");
	meshList[GEO_BALANCE2]->position.Set(-17, 10, -80);
	meshList[GEO_BALANCE2]->textureID = LoadTGA("Image//scifiwall.tga");

	//BalanceWall3
	meshList[GEO_BALANCE3] = MeshBuilder::GenerateOBJ("BalanceWall", "OBJ//BalanceWall.obj");
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

	//TEXT
	meshList[GEO_TIMEDISPLAY] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TIMEDISPLAY]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_JETPACKUI] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_JETPACKUI]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TIME] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TIME]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//alienText.tga");


}

void SP2::ScenarioRunnerInit()
{
	meshList[GEO_RAINBOW] = MeshBuilder::GenerateOBJ("RainbowRoad", "OBJ//RainbowRoad.obj");
	meshList[GEO_RAINBOW]->position.Set(0, 250, 0);
	meshList[GEO_RAINBOW]->textureID = LoadTGA("Image//RainbowRoad.tga");

	meshList[GEO_ROCK1] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK1]->position.Set(-10, 256, -425);
	meshList[GEO_ROCK1]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK2] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK2]->position.Set(10, 256, -425);
	meshList[GEO_ROCK2]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK3] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK3]->position.Set(-10, 256, -385);
	meshList[GEO_ROCK3]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK4] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK4]->position.Set(0, 256, -385);
	meshList[GEO_ROCK4]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK5] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK5]->position.Set(10, 256, -345);
	meshList[GEO_ROCK5]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK6] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK6]->position.Set(0, 256, -345);
	meshList[GEO_ROCK6]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK7] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK7]->position.Set(-10, 256, -305);
	meshList[GEO_ROCK7]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK8] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK8]->position.Set(10, 256, -305);
	meshList[GEO_ROCK8]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK9] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK9]->position.Set(0, 256, -265);
	meshList[GEO_ROCK9]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK10] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK10]->position.Set(10, 256, -225);
	meshList[GEO_ROCK10]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK11] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK11]->position.Set(-10, 256, -225);
	meshList[GEO_ROCK11]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK12] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK12]->position.Set(10, 256, -185);
	meshList[GEO_ROCK12]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK13] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK13]->position.Set(-10, 256, -145);
	meshList[GEO_ROCK13]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK14] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK14]->position.Set(0, 256, -105);
	meshList[GEO_ROCK14]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK15] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK15]->position.Set(-10, 256, -105);
	meshList[GEO_ROCK15]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK16] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK16]->position.Set(0, 256, -65);
	meshList[GEO_ROCK16]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK17] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK17]->position.Set(10, 256, -65);
	meshList[GEO_ROCK17]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK18] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK18]->position.Set(10, 256, -25);
	meshList[GEO_ROCK18]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK19] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK19]->position.Set(-10, 256, -25);
	meshList[GEO_ROCK19]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK20] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK20]->position.Set(0, 256, 15);
	meshList[GEO_ROCK20]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK21] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK21]->position.Set(10, 256, 55);
	meshList[GEO_ROCK21]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK22] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK22]->position.Set(-10, 256, 55);
	meshList[GEO_ROCK22]->textureID = LoadTGA("Image//Rock.tga");


	meshList[GEO_ROCK23] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK23]->position.Set(-10, 256, 95);
	meshList[GEO_ROCK23]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK24] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK24]->position.Set(0, 256, 95);
	meshList[GEO_ROCK24]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK25] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK25]->position.Set(10, 256, 135);
	meshList[GEO_ROCK25]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK26] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK26]->position.Set(0, 256, 135);
	meshList[GEO_ROCK26]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK27] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK27]->position.Set(-10, 256, 175);
	meshList[GEO_ROCK27]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK28] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK28]->position.Set(10, 256, 175);
	meshList[GEO_ROCK28]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK29] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK29]->position.Set(10, 256, 215);
	meshList[GEO_ROCK29]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK30] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK30]->position.Set(0, 256, 215);
	meshList[GEO_ROCK30]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK31] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK31]->position.Set(10, 256, 255);
	meshList[GEO_ROCK31]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK32] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK32]->position.Set(-10, 256, 255);
	meshList[GEO_ROCK32]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK33] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK33]->position.Set(-10, 256, 295);
	meshList[GEO_ROCK33]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK34] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK34]->position.Set(0, 256, 295);
	meshList[GEO_ROCK34]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK35] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK35]->position.Set(10, 256, 335);
	meshList[GEO_ROCK35]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK36] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK36]->position.Set(-10, 256, 335);
	meshList[GEO_ROCK36]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK37] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK37]->position.Set(10, 256, 385);
	meshList[GEO_ROCK37]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_ROCK38] = MeshBuilder::GenerateOBJ("Rocks", "OBJ//Rock.obj");
	meshList[GEO_ROCK38]->position.Set(0, 256, 385);
	meshList[GEO_ROCK38]->textureID = LoadTGA("Image//Rock.tga");

	meshList[GEO_FINALSHIP] = MeshBuilder::GenerateOBJ("Final Ship", "OBJ//FinalShip.obj");
	meshList[GEO_FINALSHIP]->position.Set(0, 256, 440);
	meshList[GEO_FINALSHIP]->textureID = LoadTGA("Image//FinalShip.tga");


}

void SP2::ButtonPress(double mouseX, double mouseY)
{
	if (mouseX > Start.mini.x && mouseX < Start.maxi.x &&
		mouseY > Start.mini.y && mouseY < Start.maxi.y)
	{
		meshList[GEO_MAINMENUBOX1] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 1, 0));
		if (Application::IsKeyPressed(VK_LBUTTON))
		{
			state = DISABLE_MOUSE;
		}

	}
	else
	{
		meshList[GEO_MAINMENUBOX1] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 0, 0));
	}
	if (mouseX > Quit.mini.x && mouseX < Quit.maxi.x &&
		mouseY > Quit.mini.y && mouseY < Quit.maxi.y)
	{
		meshList[GEO_MAINMENUBOX2] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 1, 0));
		if (Application::IsKeyPressed(VK_LBUTTON))
		{
			Application::run = false;
		}
	}
	else
	{
		meshList[GEO_MAINMENUBOX2] = MeshBuilder::GenerateQuad("Box Around Text", Color(1, 0, 0));
	}
}

Color SP2::colorRun(Vector3 position)
{
	if (15 > position.x && position.x > 10)
	{
		//red (1, 0, 0)
		//pink (1, 0, 1)
		//red and pink
		Color color(1, 0, 1 / (position.x - 10));
		return color;
	}
	else if (10 > position.x && position.x > 3)
	{
		Color color(position.x / 10, 0, 1);
		return color; 
	}
	else if (3 > position.x && position.x > -1)
	{
		Color color(0, 1 / abs(position.x), 1);
		return color;
	}
	else if (-1 > position.x && position.x > -5)
	{
		Color color(0, 1, (5 + position.x)/5);
		return color;
	}
	else if (-5 > position.x && position.x > -10)
	{
		Color color((abs(position.x)-5)/5, 1, 0);
		return color;
	}
	else if (-10 > position.x && position.x > -15)
	{
		Color color(1, 1 / (abs(position.x)-10), 0);
		return color;
	}

	return Color(1, 0, 0);
}

void SP2::Update(double dt)
{
	glfwGetCursorPos(Application::m_window, &Application::mouseX, &Application::mouseY);
	switch (state)
	{

	case MAIN_MENU:
		ButtonPress(Application::mouseX, Application::mouseY);
		break;
	case DISABLE_MOUSE:
		glfwSetInputMode(Application::m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		state = SCENARIO1;
		break;
	case SCENARIO1:
		if (!player.isDead())
		{
			player.currentItems(dt, camera, meshList);
			time += dt;
			fps = 1 / dt;
			if (player.shop.openShop == false)
			{
				move.MovementCharac(dt, camera, meshList, GEO_LONGWALL, GEO_TEXT);
				camera.Update(dt);
			}
			shoot.ShootingBullets(camera, dt, time, meshList, player);
			for (int i = 0; i < 3; ++i)
			{
				shoot.bulletHitDetection(allAliens, dt, camera);
			}
			coin.pickup(camera, player);
			if (events[3].TriggerEvent(dt, camera, time))
			{
				camera.position = Vector3(18, 15, -243);
				camera.horiRot = 0;
				camera.vertRot = 0;
				camera.target = camera.view + camera.position;
				events[3].triggered = false;
			}
			shoot.reloadClip(player, dt, time);
			coin.pickup(camera, player);
			if (events[0].TriggerEvent(dt, camera, time))
			{
				state = TRANSITION1;
			}
			glfwSetCursorPos(Application::m_window, 1280 / 2, 720 / 2);
		}
		break;
	case TRANSITION1:
		time += dt;
		break;
	case SCENARIO2:
		if (!player.isDead())
		{
			if (shoot.shooting)
			{
				light[3].position.Set(camera.position.x + camera.view.x, camera.position.y + camera.view.y, camera.position.z + camera.view.z);
				light[3].spotDirection.Set(-camera.view.x, -camera.view.y, -camera.view.z);
				light[3].power = 10;
				glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
			}
			else
			{
				light[3].power = 0;
				glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
			}
			player.currentItems(dt, camera, meshList);
			time += dt;
			fps = 1 / dt;
			move.MovementCharac(dt, camera, meshList, GEO_ARENAFRONTWALL1, GEO_RAINBOW);
			camera.Update(dt);
			shoot.ShootingBullets(camera, dt, time, meshList, player);
			for (int i = 0; i < 3; ++i)
			{
				shoot.bulletHitDetection(allAliens, dt, camera);
			}
			shoot.reloadClip(player, dt, time);	
			for (int i = 0; i < 2; ++i)
			{
				for (int i = 0; i < allAliens.size(); i++)
				{
					allAliens[i].move(camera, meshList, GEO_ARENAFRONTWALL1, GEO_RAINBOW, time, dt, player);
				}
			}
			for (int i = 0; i < allAliens.size(); i++)
			{
				allAliens[i].findPath(camera, meshList, GEO_ARENAFRONTWALL1, GEO_RAINBOW);
			}
			coin.pickup(camera, player);
			if (Application::IsKeyPressed('Q'))
			{
				AI::deathCount = 9;
			}
			if (AI::deathCount >= 9)
			{
				//subs.init(time);
				//subs.run(dt);
				if (events[1].TriggerEvent(dt, camera, time))
				{
					state = TRANSITION2;
				}
			}
			glfwSetCursorPos(Application::m_window, 1280 / 2, 720 / 2);
			break;
		}
	case TRANSITION2:
		time += dt;
		break;
	case SCENARIO3:
		if (!player.isDead())
		{
			cout << camera.position << endl;
			player.currentItems(dt, camera, meshList);
			time += dt;
			fps = 1 / dt;
			move.MovementRunner(dt, camera, meshList, GEO_LONGWALL, GEO_TEXT);
			camera.Update(dt, true);
			meshList[GEO_RUNNERSCREEN] = MeshBuilder::GenerateQuad("RUNSCREEN", colorRun(camera.position));
			coin.pickup(camera, player);
			if (events[4].TriggerEvent(dt, camera, time))
			{
				camera.position = Vector3(0, 350, -443);
				camera.horiRot = 0;
				camera.vertRot = 0;
				camera.target = camera.view + camera.position;
				events[4].triggered = false;

			}
			if (events[2].TriggerEvent(dt, camera, time))
			{
				state = ENDING;
			}
			glfwSetCursorPos(Application::m_window, 1280 / 2, 720 / 2);
			break;
	case ENDING:
		time += dt;
		if (!events[2].rendering)
		{
			Application::run = false;
		}
		break;
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

void SP2::RenderMesh(Mesh * mesh, bool enableLight, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL])
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

void SP2::RenderText(Mesh* mesh, std::string text, Color color, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL])
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	//glDisable(GL_DEPTH_TEST);
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
		Mtx44 MVP = ps.Top() * vs.Top() * ms.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST);
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
	
	if (mesh == meshList[GEO_MAINMENU])
	{
		modelStack.Rotate(-90, 0, 1, 0);
	}

	if (mesh == meshList[GEO_GAMEOVER])
	{
		modelStack.Rotate(-90, 0, 1, 0);
	}
	if (mesh == meshList[GEO_SHOPMENU])
	{
		modelStack.Rotate(-90, 0, 1, 0);
	}
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(mesh, false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void SP2::RenderOBJonScreen(Mesh* mesh, float sizex, float sizey, float x, float y, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL])
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -500, 500); //size of screen UI
	//Mtx44 projection;
	//ortho.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);

	ps.PushMatrix();
	ps.LoadMatrix(ortho);
	vs.PushMatrix();
	vs.LoadIdentity(); //No need camera for ortho mode
	ms.PushMatrix();
	ms.LoadIdentity(); //Reset modelStack
	ms.Translate(x, y, 0);
	ms.Scale(sizex, sizey, 1);
	ms.Rotate(90, 1, 0, 0);
	Mtx44 MVP = ps.Top() * vs.Top() * ms.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(mesh, false, ms, vs, ps, m_parameters);
	ps.PopMatrix();
	vs.PopMatrix();
	ms.PopMatrix();

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

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, MS ms, MS vs, MS ps, unsigned int m_parameters[U_TOTAL])
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	ps.PushMatrix();
	ps.LoadMatrix(ortho);
	vs.PushMatrix();
	vs.LoadIdentity(); //No need camera for ortho mode
	ms.PushMatrix();
	ms.LoadIdentity(); //Reset modelStack
	ms.Translate(x, y, 0);
	ms.Scale(size, size, size);
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
		Mtx44 MVP = ps.Top() * vs.Top() * ms.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	ps.PopMatrix();
	vs.PopMatrix();
	ms.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SP2::ScenarioArenaRender()
{
	//FloorShip

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_STORE]->position.x, meshList[GEO_STORE]->position.y, meshList[GEO_STORE]->position.z);
	RenderMesh(meshList[GEO_STORE], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_GROUND]->position.x, meshList[GEO_GROUND]->position.y, meshList[GEO_GROUND]->position.z);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();


	modelStack.Translate(meshList[GEO_ARENAFRONTWALL1]->position.x, meshList[GEO_ARENAFRONTWALL1]->position.y, meshList[GEO_ARENAFRONTWALL1]->position.z);
	RenderMesh(meshList[GEO_ARENAFRONTWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();

	modelStack.Translate(meshList[GEO_ARENAFRONTWALL2]->position.x, meshList[GEO_ARENAFRONTWALL2]->position.y, meshList[GEO_ARENAFRONTWALL2]->position.z);
	RenderMesh(meshList[GEO_ARENAFRONTWALL2], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	
	modelStack.Translate(meshList[GEO_ARENAFRONTWALL3]->position.x, meshList[GEO_ARENAFRONTWALL3]->position.y, meshList[GEO_ARENAFRONTWALL3]->position.z);
	RenderMesh(meshList[GEO_ARENAFRONTWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENALEFTWALL]->position.x, meshList[GEO_ARENALEFTWALL]->position.y, meshList[GEO_ARENALEFTWALL]->position.z);
	RenderMesh(meshList[GEO_ARENALEFTWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENARIGHTWALL]->position.x, meshList[GEO_ARENARIGHTWALL]->position.y, meshList[GEO_ARENARIGHTWALL]->position.z);
	RenderMesh(meshList[GEO_ARENARIGHTWALL], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENABACKWALL1]->position.x, meshList[GEO_ARENABACKWALL1]->position.y, meshList[GEO_ARENABACKWALL1]->position.z);
	RenderMesh(meshList[GEO_ARENABACKWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENABACKWALL2]->position.x, meshList[GEO_ARENABACKWALL2]->position.y, meshList[GEO_ARENABACKWALL2]->position.z);
	RenderMesh(meshList[GEO_ARENABACKWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ARENABACKWALL3]->position.x, meshList[GEO_ARENABACKWALL3]->position.y, meshList[GEO_ARENABACKWALL3]->position.z);
	RenderMesh(meshList[GEO_ARENABACKWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	
	modelStack.Translate(meshList[GEO_LANDINGPAD1]->position.x, meshList[GEO_LANDINGPAD1]->position.y, meshList[GEO_LANDINGPAD1]->position.z);
	RenderMesh(meshList[GEO_LANDINGPAD1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LANDINGPAD2]->position.x, meshList[GEO_LANDINGPAD2]->position.y, meshList[GEO_LANDINGPAD2]->position.z);
	RenderMesh(meshList[GEO_LANDINGPAD2], true);

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FRONTINTERSECTWALL]->position.x, meshList[GEO_FRONTINTERSECTWALL]->position.y, meshList[GEO_FRONTINTERSECTWALL]->position.z);
	RenderMesh(meshList[GEO_FRONTINTERSECTWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_BACKINTERSECTWALL]->position.x, meshList[GEO_BACKINTERSECTWALL]->position.y, meshList[GEO_BACKINTERSECTWALL]->position.z);
	RenderMesh(meshList[GEO_BACKINTERSECTWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RIGHTINTERSECTWALL]->position.x, meshList[GEO_RIGHTINTERSECTWALL]->position.y, meshList[GEO_RIGHTINTERSECTWALL]->position.z);
	RenderMesh(meshList[GEO_RIGHTINTERSECTWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_LEFTINTERSECTWALL]->position.x, meshList[GEO_LEFTINTERSECTWALL]->position.y, meshList[GEO_LEFTINTERSECTWALL]->position.z);
	RenderMesh(meshList[GEO_LEFTINTERSECTWALL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_MIDDLEPILLAR]->position.x, meshList[GEO_MIDDLEPILLAR]->position.y, meshList[GEO_MIDDLEPILLAR]->position.z);
	RenderMesh(meshList[GEO_MIDDLEPILLAR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//	modelStack.Scale(500, 500, 500);
	modelStack.Translate(meshList[GEO_DOOR]->position.x, meshList[GEO_DOOR]->position.y, meshList[GEO_DOOR]->position.z);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL1]->position.x, meshList[GEO_1STMAZEWALL1]->position.y, meshList[GEO_1STMAZEWALL1]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL2]->position.x, meshList[GEO_1STMAZEWALL2]->position.y, meshList[GEO_1STMAZEWALL2]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL3]->position.x, meshList[GEO_1STMAZEWALL3]->position.y, meshList[GEO_1STMAZEWALL3]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL4]->position.x, meshList[GEO_1STMAZEWALL4]->position.y, meshList[GEO_1STMAZEWALL4]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL5]->position.x, meshList[GEO_1STMAZEWALL5]->position.y, meshList[GEO_1STMAZEWALL5]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL6]->position.x, meshList[GEO_1STMAZEWALL6]->position.y, meshList[GEO_1STMAZEWALL6]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_1STMAZEWALL7]->position.x, meshList[GEO_1STMAZEWALL7]->position.y, meshList[GEO_1STMAZEWALL7]->position.z);
	RenderMesh(meshList[GEO_1STMAZEWALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL1]->position.x, meshList[GEO_2NDMAZEWALL1]->position.y, meshList[GEO_2NDMAZEWALL1]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL2]->position.x, meshList[GEO_2NDMAZEWALL2]->position.y, meshList[GEO_2NDMAZEWALL2]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL3]->position.x, meshList[GEO_2NDMAZEWALL3]->position.y, meshList[GEO_2NDMAZEWALL3]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL4]->position.x, meshList[GEO_2NDMAZEWALL4]->position.y, meshList[GEO_2NDMAZEWALL4]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL5]->position.x, meshList[GEO_2NDMAZEWALL5]->position.y, meshList[GEO_2NDMAZEWALL5]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_2NDMAZEWALL6]->position.x, meshList[GEO_2NDMAZEWALL6]->position.y, meshList[GEO_2NDMAZEWALL6]->position.z);
	RenderMesh(meshList[GEO_2NDMAZEWALL6], true);
	modelStack.PopMatrix();

	// THIRD WALL
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL1]->position.x, meshList[GEO_3RDMAZEWALL1]->position.y, meshList[GEO_3RDMAZEWALL1]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL2]->position.x, meshList[GEO_3RDMAZEWALL2]->position.y, meshList[GEO_3RDMAZEWALL2]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL3]->position.x, meshList[GEO_3RDMAZEWALL3]->position.y, meshList[GEO_3RDMAZEWALL3]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL4]->position.x, meshList[GEO_3RDMAZEWALL4]->position.y, meshList[GEO_3RDMAZEWALL4]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL5]->position.x, meshList[GEO_3RDMAZEWALL5]->position.y, meshList[GEO_3RDMAZEWALL5]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL6]->position.x, meshList[GEO_3RDMAZEWALL6]->position.y, meshList[GEO_3RDMAZEWALL6]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL7]->position.x, meshList[GEO_3RDMAZEWALL7]->position.y, meshList[GEO_3RDMAZEWALL7]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_3RDMAZEWALL8]->position.x, meshList[GEO_3RDMAZEWALL8]->position.y, meshList[GEO_3RDMAZEWALL8]->position.z);
	RenderMesh(meshList[GEO_3RDMAZEWALL8], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL1]->position.x, meshList[GEO_4THMAZEWALL1]->position.y, meshList[GEO_4THMAZEWALL1]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL2]->position.x, meshList[GEO_4THMAZEWALL2]->position.y, meshList[GEO_4THMAZEWALL2]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	
	modelStack.Translate(meshList[GEO_4THMAZEWALL3]->position.x, meshList[GEO_4THMAZEWALL3]->position.y, meshList[GEO_4THMAZEWALL3]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL4]->position.x, meshList[GEO_4THMAZEWALL4]->position.y, meshList[GEO_4THMAZEWALL4]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL5]->position.x, meshList[GEO_4THMAZEWALL5]->position.y, meshList[GEO_4THMAZEWALL5]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL6]->position.x, meshList[GEO_4THMAZEWALL6]->position.y, meshList[GEO_4THMAZEWALL6]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL7]->position.x, meshList[GEO_4THMAZEWALL7]->position.y, meshList[GEO_4THMAZEWALL7]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_4THMAZEWALL8]->position.x, meshList[GEO_4THMAZEWALL8]->position.y, meshList[GEO_4THMAZEWALL8]->position.z);
	RenderMesh(meshList[GEO_4THMAZEWALL8], true);
	modelStack.PopMatrix();

	

}

void SP2::ScenarioParkourRender()
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


}

void SP2::ScenarioRunnerRender()
{
	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_RAINBOW]->position.x, meshList[GEO_RAINBOW]->position.y, meshList[GEO_RAINBOW]->position.z);
	RenderMesh(meshList[GEO_RAINBOW], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK1]->position.x, meshList[GEO_ROCK1]->position.y, meshList[GEO_ROCK1]->position.z);
	RenderMesh(meshList[GEO_ROCK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK2]->position.x, meshList[GEO_ROCK2]->position.y, meshList[GEO_ROCK2]->position.z);
	RenderMesh(meshList[GEO_ROCK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK3]->position.x, meshList[GEO_ROCK3]->position.y, meshList[GEO_ROCK3]->position.z);
	RenderMesh(meshList[GEO_ROCK3], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK4]->position.x, meshList[GEO_ROCK4]->position.y, meshList[GEO_ROCK4]->position.z);
	RenderMesh(meshList[GEO_ROCK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK5]->position.x, meshList[GEO_ROCK5]->position.y, meshList[GEO_ROCK5]->position.z);
	RenderMesh(meshList[GEO_ROCK5], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK6]->position.x, meshList[GEO_ROCK6]->position.y, meshList[GEO_ROCK6]->position.z);
	RenderMesh(meshList[GEO_ROCK6], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK7]->position.x, meshList[GEO_ROCK7]->position.y, meshList[GEO_ROCK7]->position.z);
	RenderMesh(meshList[GEO_ROCK7], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK8]->position.x, meshList[GEO_ROCK8]->position.y, meshList[GEO_ROCK8]->position.z);
	RenderMesh(meshList[GEO_ROCK8], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK9]->position.x, meshList[GEO_ROCK9]->position.y, meshList[GEO_ROCK9]->position.z);
	RenderMesh(meshList[GEO_ROCK9], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK10]->position.x, meshList[GEO_ROCK10]->position.y, meshList[GEO_ROCK10]->position.z);
	RenderMesh(meshList[GEO_ROCK10], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK11]->position.x, meshList[GEO_ROCK11]->position.y, meshList[GEO_ROCK11]->position.z);
	RenderMesh(meshList[GEO_ROCK11], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK12]->position.x, meshList[GEO_ROCK12]->position.y, meshList[GEO_ROCK12]->position.z);
	RenderMesh(meshList[GEO_ROCK12], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK13]->position.x, meshList[GEO_ROCK13]->position.y, meshList[GEO_ROCK13]->position.z);
	RenderMesh(meshList[GEO_ROCK13], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK14]->position.x, meshList[GEO_ROCK14]->position.y, meshList[GEO_ROCK14]->position.z);
	RenderMesh(meshList[GEO_ROCK14], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK15]->position.x, meshList[GEO_ROCK15]->position.y, meshList[GEO_ROCK15]->position.z);
	RenderMesh(meshList[GEO_ROCK15], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK16]->position.x, meshList[GEO_ROCK16]->position.y, meshList[GEO_ROCK16]->position.z);
	RenderMesh(meshList[GEO_ROCK16], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK17]->position.x, meshList[GEO_ROCK17]->position.y, meshList[GEO_ROCK17]->position.z);
	RenderMesh(meshList[GEO_ROCK17], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK18]->position.x, meshList[GEO_ROCK18]->position.y, meshList[GEO_ROCK18]->position.z);
	RenderMesh(meshList[GEO_ROCK18], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK19]->position.x, meshList[GEO_ROCK19]->position.y, meshList[GEO_ROCK19]->position.z);
	RenderMesh(meshList[GEO_ROCK19], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK20]->position.x, meshList[GEO_ROCK20]->position.y, meshList[GEO_ROCK20]->position.z);
	RenderMesh(meshList[GEO_ROCK20], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK21]->position.x, meshList[GEO_ROCK21]->position.y, meshList[GEO_ROCK21]->position.z);
	RenderMesh(meshList[GEO_ROCK21], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK22]->position.x, meshList[GEO_ROCK22]->position.y, meshList[GEO_ROCK22]->position.z);
	RenderMesh(meshList[GEO_ROCK22], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK23]->position.x, meshList[GEO_ROCK23]->position.y, meshList[GEO_ROCK23]->position.z);
	RenderMesh(meshList[GEO_ROCK23], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK24]->position.x, meshList[GEO_ROCK24]->position.y, meshList[GEO_ROCK24]->position.z);
	RenderMesh(meshList[GEO_ROCK24], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK25]->position.x, meshList[GEO_ROCK25]->position.y, meshList[GEO_ROCK25]->position.z);
	RenderMesh(meshList[GEO_ROCK25], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK26]->position.x, meshList[GEO_ROCK26]->position.y, meshList[GEO_ROCK26]->position.z);
	RenderMesh(meshList[GEO_ROCK26], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK27]->position.x, meshList[GEO_ROCK27]->position.y, meshList[GEO_ROCK27]->position.z);
	RenderMesh(meshList[GEO_ROCK27], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK28]->position.x, meshList[GEO_ROCK28]->position.y, meshList[GEO_ROCK28]->position.z);
	RenderMesh(meshList[GEO_ROCK28], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK29]->position.x, meshList[GEO_ROCK29]->position.y, meshList[GEO_ROCK29]->position.z);
	RenderMesh(meshList[GEO_ROCK29], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK30]->position.x, meshList[GEO_ROCK30]->position.y, meshList[GEO_ROCK30]->position.z);
	RenderMesh(meshList[GEO_ROCK30], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK31]->position.x, meshList[GEO_ROCK31]->position.y, meshList[GEO_ROCK31]->position.z);
	RenderMesh(meshList[GEO_ROCK31], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK32]->position.x, meshList[GEO_ROCK32]->position.y, meshList[GEO_ROCK32]->position.z);
	RenderMesh(meshList[GEO_ROCK32], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK33]->position.x, meshList[GEO_ROCK33]->position.y, meshList[GEO_ROCK33]->position.z);
	RenderMesh(meshList[GEO_ROCK33], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK34]->position.x, meshList[GEO_ROCK34]->position.y, meshList[GEO_ROCK34]->position.z);
	RenderMesh(meshList[GEO_ROCK34], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK35]->position.x, meshList[GEO_ROCK35]->position.y, meshList[GEO_ROCK35]->position.z);
	RenderMesh(meshList[GEO_ROCK35], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK36]->position.x, meshList[GEO_ROCK36]->position.y, meshList[GEO_ROCK36]->position.z);
	RenderMesh(meshList[GEO_ROCK36], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK37]->position.x, meshList[GEO_ROCK37]->position.y, meshList[GEO_ROCK37]->position.z);
	RenderMesh(meshList[GEO_ROCK37], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_ROCK38]->position.x, meshList[GEO_ROCK38]->position.y, meshList[GEO_ROCK38]->position.z);
	RenderMesh(meshList[GEO_ROCK38], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(meshList[GEO_FINALSHIP]->position.x, meshList[GEO_FINALSHIP]->position.y, meshList[GEO_FINALSHIP]->position.z);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_FINALSHIP], true);
	modelStack.PopMatrix();
}

void SP2::RenderCoins()
{
	for (int i = 0; i < coin.allCoins.size(); ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(coin.allCoins[i]->position.x, coin.allCoins[i]->position.y, coin.allCoins[i]->position.z);
		modelStack.Rotate(coin.rotateAngle, 0, 1, 0);
		RenderMesh(coin.allCoins[i], true);
		modelStack.PopMatrix();
	}
	coin.rotateAngle++;
}


void SP2::PlayerPoints()
{
	//points = (AI::deathCount * 50) + (coin.acquired * 10);
}


void SP2::RenderUI()
{	
	std::ostringstream timeString;
	
	timeString.str("");
	timeString << "Points: " << static_cast<int>(player.points);
	RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 1, 20);

	if (player.object)
	{
		if (player.object->name == meshList[GEO_STORE]->name)
		{
			if (player.shop.openShop == true)
			{
				RenderOBJonScreen(meshList[GEO_SHOPMENU], 80, 60, 40, 30);

				timeString.str("");
				timeString << "Points: " << static_cast<int>(player.points);
				RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 1, 20);

				timeString.str("");
				timeString << "Rifle Ammo : " << player.inv.Rifle.clip << "/" << player.inv.Rifle.ammo;
				RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(0, 1, 0), 2, 12, 18);
				timeString.str("");
				timeString << "SMG Ammo : " << player.inv.SMG.clip << "/" << player.inv.SMG.ammo;
				RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(0, 1, 0), 2, 12, 15);
				timeString.str("");
				timeString << "Pistol Ammo : " << player.inv.Pistol.clip << "/" << player.inv.Pistol.ammo;
				RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(0, 1, 0), 2, 12, 12);
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 1 to buy Rifle ammo (50 points)", Color(0, 1, 0), 2, 1, 19);
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 2 to buy SMG ammo (35 points)", Color(0, 1, 0), 2, 1, 16);
				RenderTextOnScreen(meshList[GEO_TEXT], "Press 3 to buy Pistol ammo (20 points)", Color(0, 1, 0), 2, 1, 13);
				RenderTextOnScreen(meshList[GEO_TEXT], "Press E to close Shop", Color(0, 1, 0), 2, 1, 10);

			}
			else
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Press E to Open Shop", Color(0, 1, 0), 2, 15, 15);
			}
		}
	}
	else
	{ //////////////////////////////////
		//			JetFuel             //
		/////////////////////////////////
		if (move.jetPack.getStatus() == false && (fmod(time, 0.2) < 0.1))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "DISABLED !!!", Color(1, 0, 0), 2, 1, 7);
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

		if (move.jetPack.getFuel() > 80)
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
		timeString.str("");
		RenderTextOnScreen(meshList[GEO_TEXT], "Time: ", Color(1, 0, 0), 2, 2, 25);
		
		timeString << std::setprecision(3) << time;
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 3, 24);

		timeString.str("");
		timeString << "X: " << static_cast<int>(camera.position.x);
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 1, 10.4);
		timeString.str("");
		timeString << "Y: " << static_cast<int>(camera.position.y);
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 1, 9.4);
		timeString.str("");
		timeString << "Z: " << static_cast<int>(camera.position.z);
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(1, 0, 0), 2, 1, 8.4);


		//PlayerPoints();

	




		//////////////////////////////////
		//			Gun                //
		/////////////////////////////////
		RenderTextOnScreen(meshList[GEO_TEXT], "Gun Mode: ", Color(0, 1, 0), 2, 30, 6);
		if (player.inv.GunSelected->semiAuto == false)
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


		/*RenderTextOnScreen(meshList[GEO_TEXT], "Ammo: ", Color(0, 1, 0), 2, 28,20);*/

		/*timeString.str("");
		timeString << player.inv.GunSelected->ammo;
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str() ,Color(0,1,0), 2, 35, 20);*/
		//UI Background Panal
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_UIBG], 25, 19, 72, 3.5);
		modelStack.PopMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Player's Health
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_PLAYERHEALTH], 30 * player.getScaleHealth(), 1, 40, 55);
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
		RenderOBJonScreen(meshList[GEO_HELMET], 80, 60, 40, 30);
		modelStack.PopMatrix();
		timeString.str("");
		timeString << "Ammo : " << player.inv.GunSelected->clip << "/" << player.inv.GunSelected->ammo;
		RenderTextOnScreen(meshList[GEO_TEXT], timeString.str(), Color(0, 1, 0), 2, 19, 8);
		if (player.inv.GunSelected->clip == 0)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload Needed, Press R to Reload", Color(0, 1, 0), 2, 1, 15);
		}

	}
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

	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[2].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[2].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if (light[3].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[3].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
	}
	
	switch (state)
	{
	case MAIN_MENU:
		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_MAINMENUBOX1], 30, 5, 44, 25);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_MAINMENUBOX2], 30, 5, 44, 17);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderOBJonScreen(meshList[GEO_MAINMENU], 80, 60, 40, 30);
		modelStack.PopMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Start Game", Color(0, 0, 0), 3, 10, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(0, 0, 0), 3, 10.5, 5.3);
		break;
	case SCENARIO1:
		//Skybox
		RenderSkybox(camera.position);

		for (int a = 0; a < shoot.bullets.size(); a++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(shoot.bullets[a].Position.x, shoot.bullets[a].Position.y, shoot.bullets[a].Position.z);
			modelStack.Scale(0.5, 0.5, 0.5);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}

		//RenderCoins
		RenderCoins();
		//Render Scenario3
		ScenarioParkourRender();
		//Render ScenarioRunner
		//ScenarioRunnerRender();
		RenderUI();
		break;
	case TRANSITION1:
		if (!events[0].renderTransition(time, camera, modelStack, viewStack, projectionStack, m_parameters, meshList[GEO_TEXT], meshList[GEO_BLACKSCREEN]))
		{
			state = SCENARIO2;
		}
		break;
	case SCENARIO2:
		ScenarioArenaRender();
		for (int a = 0; a < shoot.bullets.size(); a++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(shoot.bullets[a].Position.x, shoot.bullets[a].Position.y, shoot.bullets[a].Position.z);
			modelStack.Scale(0.5, 0.5, 0.5);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
		RenderCoins();
		for (int i = 0; i < allAliens.size(); i++)
		{
			allAliens[i].renderAlien(true, modelStack, viewStack, projectionStack, m_parameters, meshList, player);
		}

		RenderUI();
		break;
	case TRANSITION2:
		if (!events[1].renderTransition(time, camera, modelStack, viewStack, projectionStack, m_parameters, meshList[GEO_TEXT], meshList[GEO_BLACKSCREEN]))
		{
			state = SCENARIO3;
		}
		break;

	case SCENARIO3:
		//Skybox
		RenderSkybox(camera.position);
		ScenarioRunnerRender();
		RenderCoins();
		glUniform1f(m_parameters[U_MATERIAL_TRANSPARENCY], 0.2);
		RenderOBJonScreen(meshList[GEO_RUNNERSCREEN], 100, 100, 40, 30);
		glUniform1f(m_parameters[U_MATERIAL_TRANSPARENCY], 1);
		break;
	case ENDING:
		RenderOBJonScreen(meshList[GEO_GAMEOVER], 80, 60, 40, 30);
		events[2].renderTransition(time, camera, modelStack, viewStack, projectionStack, m_parameters, meshList[GEO_TEXT], meshList[GEO_BLACKSCREEN]);
		std::ostringstream pointsDisplay;
		pointsDisplay << "Total Points Earned: " << player.points;
		RenderTextOnScreen(meshList[GEO_TEXT], pointsDisplay.str(), Color(1, 0, 0), 3, 0, 0);
		highscore.data.push_back(player.points);
		std::ofstream OutputFile("Scores//HighScore.txt");
		vector<int> temp(highscore.data);
		highscore.data.clear();
		int highestscore = 0;
		int slot = 0;
		while (temp.size() > 0)
		{
			for (int i = 0; i < temp.size(); ++i)
			{
				if (temp[i] > highestscore)
				{
					highestscore = temp[i];
					slot = i;
				}
			}
			cout << temp.size() << endl;
			temp.erase(temp.begin() + slot);
			highscore.data.push_back(highestscore);
			highestscore = 0;
			if (slot <= 0)
			{
				break;
			}
		}
		for (int i = 0; i < highscore.data.size(); ++i)
		{
			OutputFile << highscore.data[i] << '\n';
		}
		OutputFile.close();
		for (int i = 0; i < highscore.data.size(); ++i)
		{
			pointsDisplay.str("");
			pointsDisplay << highscore.data[i];
			RenderTextOnScreen(meshList[GEO_TEXT], pointsDisplay.str(), Color(1, 0, 0), 3, 10, 5-i);
		}

	}
}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

