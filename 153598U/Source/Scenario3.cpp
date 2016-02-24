#include "Scenario3.h"
#include "SP2.h"
#include "LoadTGA.h"
#include "MeshBuilder.h"

void scenario3::generateMeshList(Mesh ** meshList)
{
	//ShipFloor
	meshList[SP2::GEO_SHIPFLOOR] = MeshBuilder::GenerateOBJ("Floor", "OBJ//ShipFloor.obj");
	meshList[SP2::GEO_SHIPFLOOR]->textureID = LoadTGA("Image//ShipFloor.tga");
	meshList[SP2::GEO_SHIPFLOOR]->position.Set(0, -2, 0);
	meshList[SP2::GEO_SHIPFLOOR]->interactable = true;

	//ShipCeiling
	meshList[SP2::SP2::GEO_SHIPCEILING] = MeshBuilder::GenerateOBJ("Ceiling", "OBJ//Ceiling.obj");
	//meshList[SP2::SP2::GEO_SHIPFLOOR]->textureID = LoadTGA("Image//ShipFloor.tga");
	meshList[SP2::SP2::GEO_SHIPCEILING]->position.Set(0, 23.5, 0);
	meshList[SP2::SP2::GEO_SHIPCEILING]->interactable = true;

	//ShipCeiling
	meshList[SP2::GEO_SHIPTOP] = MeshBuilder::GenerateOBJ("Ceiling", "OBJ//ShipTop.obj");
	//meshList[SP2::SP2::GEO_SHIPTOP]->textureID = LoadTGA("Image//Ship.tga");
	meshList[SP2::GEO_SHIPTOP]->position.Set(0, -9, 0);
	meshList[SP2::GEO_SHIPTOP]->interactable = true;

	//Arun's Wall
	//meshList[SP2::SP2::GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");
	meshList[SP2::GEO_FUEL1] = MeshBuilder::GenerateQuad("fuel1", Color(0.8, 0, 0));
	meshList[SP2::GEO_FUEL2] = MeshBuilder::GenerateQuad("fuel2", Color(1, 0, 0));
	meshList[SP2::GEO_FUEL3] = MeshBuilder::GenerateQuad("fuel3", Color(0, 0.8, 0));
	meshList[SP2::GEO_FUEL4] = MeshBuilder::GenerateQuad("fuel4", Color(0, 1, 0));
	meshList[SP2::GEO_FUEL5] = MeshBuilder::GenerateQuad("fuel5", Color(0.2, 1, 0.2));
	meshList[SP2::GEO_JETPACKUI] = MeshBuilder::GenerateQuad("Jetpack UI", Color(1, 2, 1));

	////GROUND
	/*meshList[SP2::SP2::GEO_GROUND] = MeshBuilder::GenerateGround("ground", Color(0.2, 0.2, 0.2));
	meshList[SP2::SP2::GEO_GROUND]->textureID = LoadTGA("Image//sand.tga");*/

	////Arun Wall Left
	meshList[SP2::GEO_LEFTWALL1] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL1]->position.Set(20, 0, 0);
	meshList[SP2::GEO_LEFTWALL1]->interactable = true;

	meshList[SP2::GEO_LEFTWALL2] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL2]->position.Set(20, 0, 35);
	meshList[SP2::GEO_LEFTWALL2]->interactable = true;

	meshList[SP2::GEO_LEFTWALL3] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL3]->position.Set(20, 0, 70);
	meshList[SP2::GEO_LEFTWALL3]->interactable = true;

	meshList[SP2::GEO_LEFTWALL4] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL4]->position.Set(20, 0, 105);
	meshList[SP2::GEO_LEFTWALL4]->interactable = true;

	meshList[SP2::GEO_LEFTWALL5] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL5]->position.Set(20, 0, 140);
	meshList[SP2::GEO_LEFTWALL5]->interactable = true;

	meshList[SP2::GEO_LEFTWALL6] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL6]->position.Set(20, 0, 175);
	meshList[SP2::GEO_LEFTWALL6]->interactable = true;

	meshList[SP2::GEO_LEFTWALL7] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL7]->position.Set(20, 0, 210);
	meshList[SP2::GEO_LEFTWALL7]->interactable = true;

	meshList[SP2::GEO_LEFTWALL8] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL8]->position.Set(20, 0, 245);
	meshList[SP2::GEO_LEFTWALL8]->interactable = true;

	meshList[SP2::GEO_LEFTWALL9] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL9]->position.Set(20, 0, 280);
	meshList[SP2::GEO_LEFTWALL9]->interactable = true;

	meshList[SP2::GEO_LEFTWALL10] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL10]->position.Set(20, 0, 315);
	meshList[SP2::GEO_LEFTWALL10]->interactable = true;

	meshList[SP2::GEO_LEFTWALL11] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL11]->position.Set(20, 0, 350);
	meshList[SP2::GEO_LEFTWALL11]->interactable = true;

	meshList[SP2::GEO_LEFTWALL12] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL12]->position.Set(20, 0, 385);
	meshList[SP2::GEO_LEFTWALL12]->interactable = true;

	meshList[SP2::GEO_LEFTWALL13] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL13]->position.Set(20, 0, 420);
	meshList[SP2::GEO_LEFTWALL13]->interactable = true;

	meshList[SP2::GEO_LEFTWALL14] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL14]->position.Set(20, 0, 455);
	meshList[SP2::GEO_LEFTWALL14]->interactable = true;

	meshList[SP2::GEO_LEFTWALL15] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL15]->position.Set(20, 0, 490);
	meshList[SP2::GEO_LEFTWALL15]->interactable = true;

	meshList[SP2::GEO_LEFTWALL16] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL16]->position.Set(20, 0, -35);
	meshList[SP2::GEO_LEFTWALL16]->interactable = true;

	meshList[SP2::GEO_LEFTWALL17] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL17]->position.Set(20, 0, -70);
	meshList[SP2::GEO_LEFTWALL17]->interactable = true;

	meshList[SP2::GEO_LEFTWALL18] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL18]->position.Set(20, 0, -105);
	meshList[SP2::GEO_LEFTWALL18]->interactable = true;

	meshList[SP2::GEO_LEFTWALL19] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL19]->position.Set(20, 0, -140);
	meshList[SP2::GEO_LEFTWALL19]->interactable = true;

	meshList[SP2::GEO_LEFTWALL20] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL20]->position.Set(20, 0, -175);
	meshList[SP2::GEO_LEFTWALL20]->interactable = true;

	meshList[SP2::GEO_LEFTWALL21] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL21]->position.Set(20, 0, -210);
	meshList[SP2::GEO_LEFTWALL21]->interactable = true;

	meshList[SP2::GEO_LEFTWALL22] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL22]->position.Set(20, 0, -245);
	meshList[SP2::GEO_LEFTWALL22]->interactable = true;

	meshList[SP2::GEO_LEFTWALL23] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL23]->position.Set(20, 0, -280);
	meshList[SP2::GEO_LEFTWALL23]->interactable = true;

	meshList[SP2::GEO_LEFTWALL24] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL24]->position.Set(20, 0, -315);
	meshList[SP2::GEO_LEFTWALL24]->interactable = true;

	meshList[SP2::GEO_LEFTWALL25] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL25]->position.Set(20, 0, -350);
	meshList[SP2::GEO_LEFTWALL25]->interactable = true;

	meshList[SP2::GEO_LEFTWALL26] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL26]->position.Set(20, 0, -385);
	meshList[SP2::GEO_LEFTWALL26]->interactable = true;

	meshList[SP2::GEO_LEFTWALL27] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL27]->position.Set(20, 0, -420);
	meshList[SP2::GEO_LEFTWALL27]->interactable = true;

	meshList[SP2::GEO_LEFTWALL28] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL28]->position.Set(20, 0, -455);
	meshList[SP2::GEO_LEFTWALL28]->interactable = true;

	meshList[SP2::GEO_LEFTWALL29] = MeshBuilder::GenerateOBJ("Left Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_LEFTWALL29]->position.Set(20, 0, -490);
	meshList[SP2::GEO_LEFTWALL29]->interactable = true;


	//Arun Wall Right
	meshList[SP2::GEO_RIGHTWALL1] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL1]->position.Set(-20, 0, 0);
	meshList[SP2::GEO_RIGHTWALL1]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL2] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL2]->position.Set(-20, 0, 35);
	meshList[SP2::GEO_RIGHTWALL2]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL3] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL3]->position.Set(-20, 0, 70);
	meshList[SP2::GEO_RIGHTWALL3]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL4] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL4]->position.Set(-20, 0, 105);
	meshList[SP2::GEO_RIGHTWALL4]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL5] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL5]->position.Set(-20, 0, 140);
	meshList[SP2::GEO_RIGHTWALL5]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL6] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL6]->position.Set(-20, 0, 175);
	meshList[SP2::GEO_RIGHTWALL6]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL7] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL7]->position.Set(-20, 0, 210);
	meshList[SP2::GEO_RIGHTWALL7]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL8] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL8]->position.Set(-20, 0, 245);
	meshList[SP2::GEO_RIGHTWALL8]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL9] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL9]->position.Set(-20, 0, 280);
	meshList[SP2::GEO_RIGHTWALL9]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL10] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL10]->position.Set(-20, 0, 315);
	meshList[SP2::GEO_RIGHTWALL10]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL11] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL11]->position.Set(-20, 0, 350);
	meshList[SP2::GEO_RIGHTWALL11]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL12] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL12]->position.Set(-20, 0, 385);
	meshList[SP2::GEO_RIGHTWALL12]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL13] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL13]->position.Set(-20, 0, 420);
	meshList[SP2::GEO_RIGHTWALL13]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL14] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL14]->position.Set(-20, 0, 455);
	meshList[SP2::GEO_RIGHTWALL14]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL15] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL15]->position.Set(-20, 0, 490);
	meshList[SP2::GEO_RIGHTWALL15]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL16] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL16]->position.Set(-20, 0, -35);
	meshList[SP2::GEO_RIGHTWALL16]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL17] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL17]->position.Set(-20, 0, -70);
	meshList[SP2::GEO_RIGHTWALL17]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL18] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL18]->position.Set(-20, 0, -105);
	meshList[SP2::GEO_RIGHTWALL18]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL19] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL19]->position.Set(-20, 0, -140);
	meshList[SP2::GEO_RIGHTWALL19]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL20] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL20]->position.Set(-20, 0, -175);
	meshList[SP2::GEO_RIGHTWALL20]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL21] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL21]->position.Set(-20, 0, -210);
	meshList[SP2::GEO_RIGHTWALL21]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL22] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL22]->position.Set(-20, 0, -245);
	meshList[SP2::GEO_RIGHTWALL22]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL23] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL23]->position.Set(-20, 0, -280);
	meshList[SP2::GEO_RIGHTWALL23]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL24] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL24]->position.Set(-20, 0, -315);
	meshList[SP2::GEO_RIGHTWALL24]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL25] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL25]->position.Set(-20, 0, -350);
	meshList[SP2::GEO_RIGHTWALL25]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL26] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL26]->position.Set(-20, 0, -385);
	meshList[SP2::GEO_RIGHTWALL26]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL27] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL27]->position.Set(-20, 0, -420);
	meshList[SP2::GEO_RIGHTWALL27]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL28] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL28]->position.Set(-20, 0, -455);
	meshList[SP2::GEO_RIGHTWALL28]->interactable = true;

	meshList[SP2::GEO_RIGHTWALL29] = MeshBuilder::GenerateOBJ("Right Wall", "OBJ//wall.obj");
	meshList[SP2::GEO_RIGHTWALL29]->position.Set(-20, 0, -490);
	meshList[SP2::GEO_RIGHTWALL29]->interactable = true;

	meshList[SP2::GEO_MODEL1] = MeshBuilder::GenerateOBJ("Model 1", "OBJ//wall.obj");

	meshList[SP2::GEO_MODEL1]->position.Set(10, 0, 10);
	meshList[SP2::GEO_MODEL1]->textureID = LoadTGA("Image//wallleft.tga");
	meshList[SP2::GEO_MODEL1]->interactable = true;

	//Map(FreeRun)

	//Blocks
	meshList[SP2::GEO_BLOCK1] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK1]->position.Set(10, 3, -440);
	meshList[SP2::GEO_BLOCK1]->interactable = true;

	meshList[SP2::GEO_BLOCK2] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK2]->position.Set(-10, 3, -420);
	meshList[SP2::GEO_BLOCK2]->interactable = true;

	meshList[SP2::GEO_BLOCK3] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK3]->position.Set(10, 3, -220);
	meshList[SP2::GEO_BLOCK3]->interactable = true;

	meshList[SP2::GEO_BLOCK4] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK4]->position.Set(10, 3, -200);
	meshList[SP2::GEO_BLOCK4]->interactable = true;

	meshList[SP2::GEO_BLOCK5] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK5]->position.Set(-10, 3, -220);
	meshList[SP2::GEO_BLOCK5]->interactable = true;

	meshList[SP2::GEO_BLOCK6] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK6]->position.Set(-10, 3, -200);
	meshList[SP2::GEO_BLOCK6]->interactable = true;

	meshList[SP2::GEO_BLOCK7] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK7]->position.Set(0, 3, -180);
	meshList[SP2::GEO_BLOCK7]->interactable = true;

	meshList[SP2::GEO_BLOCK8] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK8]->position.Set(10, 3, 60);
	meshList[SP2::GEO_BLOCK8]->interactable = true;

	meshList[SP2::GEO_BLOCK9] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK9]->position.Set(-10, 3, 60);
	meshList[SP2::GEO_BLOCK9]->interactable = true;

	meshList[SP2::GEO_BLOCK10] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK10]->position.Set(0, 3, 80);
	meshList[SP2::GEO_BLOCK10]->interactable = true;

	meshList[SP2::GEO_BLOCK11] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK11]->position.Set(15, 3, 120);
	meshList[SP2::GEO_BLOCK11]->interactable = true;

	meshList[SP2::GEO_BLOCK12] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK12]->position.Set(-15, 3, 120);
	meshList[SP2::GEO_BLOCK12]->interactable = true;

	meshList[SP2::GEO_BLOCK13] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK13]->position.Set(0, 3, 140);
	meshList[SP2::GEO_BLOCK13]->interactable = true;

	meshList[SP2::GEO_BLOCK14] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK14]->position.Set(0, 3, 190);
	meshList[SP2::GEO_BLOCK14]->interactable = true;

	meshList[SP2::GEO_BLOCK17] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK17]->position.Set(10, 3, 450);
	meshList[SP2::GEO_BLOCK17]->interactable = true;

	meshList[SP2::GEO_BLOCK18] = MeshBuilder::GenerateOBJ("Block", "OBJ//Block.obj");
	meshList[SP2::GEO_BLOCK18]->position.Set(-10, 3, 450);
	meshList[SP2::GEO_BLOCK18]->interactable = true;

	//Wall(Thin)
	meshList[SP2::GEO_THIN1] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN1]->position.Set(0, 3, -350);
	meshList[SP2::GEO_THIN1]->interactable = true;

	meshList[SP2::GEO_THIN2] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN2]->position.Set(0, 3, -150);
	meshList[SP2::GEO_THIN2]->interactable = true;

	meshList[SP2::GEO_THIN3] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN3]->position.Set(0, 3, 40);
	meshList[SP2::GEO_THIN3]->interactable = true;

	meshList[SP2::GEO_THIN4] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN4]->position.Set(0, 3, 230);
	meshList[SP2::GEO_THIN4]->interactable = true;

	meshList[SP2::GEO_THIN5] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN5]->position.Set(0, 3, 330);
	meshList[SP2::GEO_THIN5]->interactable = true;

	meshList[SP2::GEO_THIN6] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin).obj");
	meshList[SP2::GEO_THIN6]->position.Set(0, 3, 400);
	meshList[SP2::GEO_THIN6]->interactable = true;

	//Wall(Thin)2
	meshList[SP2::GEO_THINz1] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz1]->position.Set(0, 3, 0);
	meshList[SP2::GEO_THINz1]->interactable = true;

	meshList[SP2::GEO_THINz2] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz2]->position.Set(10, 3, 0);
	meshList[SP2::GEO_THINz2]->interactable = true;

	meshList[SP2::GEO_THINz3] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz3]->position.Set(-10, 3, 0);
	meshList[SP2::GEO_THINz3]->interactable = true;

	meshList[SP2::GEO_THINz4] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz4]->position.Set(5, 3, 30);
	meshList[SP2::GEO_THINz4]->interactable = true;

	meshList[SP2::GEO_THINz5] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz5]->position.Set(15, 3, 30);
	meshList[SP2::GEO_THINz5]->interactable = true;

	meshList[SP2::GEO_THINz6] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz6]->position.Set(-5, 3, 30);
	meshList[SP2::GEO_THINz6]->interactable = true;

	meshList[SP2::GEO_THINz7] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz7]->position.Set(-15, 3, 30);
	meshList[SP2::GEO_THINz7]->interactable = true;

	meshList[SP2::GEO_THINz8] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz8]->position.Set(10, 3, 80);
	meshList[SP2::GEO_THINz8]->interactable = true;

	meshList[SP2::GEO_THINz9] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz9]->position.Set(-10, 3, 80);
	meshList[SP2::GEO_THINz9]->interactable = true;

	meshList[SP2::GEO_THINz10] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz10]->position.Set(15, 3, 150);
	meshList[SP2::GEO_THINz10]->interactable = true;

	meshList[SP2::GEO_THINz11] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz11]->position.Set(-15, 3, 150);
	meshList[SP2::GEO_THINz11]->interactable = true;

	meshList[SP2::GEO_THINz12] = MeshBuilder::GenerateOBJ("Wall(Thin)", "OBJ//Wall(Thin)2.obj");
	meshList[SP2::GEO_THINz12]->position.Set(0, 3, 160);
	meshList[SP2::GEO_THINz12]->interactable = true;

	//Wall(Thick)
	meshList[SP2::GEO_THICK1] = MeshBuilder::GenerateOBJ("Wall(Thick)", "OBJ//Wall(Thick).obj");
	meshList[SP2::GEO_THICK1]->position.Set(0, 3, -400);
	meshList[SP2::GEO_THICK1]->interactable = true;

	meshList[SP2::GEO_THICK2] = MeshBuilder::GenerateOBJ("Wall(Thick)", "OBJ//Wall(Thick).obj");
	meshList[SP2::GEO_THICK2]->position.Set(0, 3, -50);
	meshList[SP2::GEO_THICK2]->interactable = true;

	//Turrets
	meshList[SP2::GEO_TURRET1] = MeshBuilder::GenerateOBJ("Turret", "OBJ//Turret.obj");
	meshList[SP2::GEO_TURRET1]->position.Set(60, 5, -480);
	meshList[SP2::GEO_TURRET1]->interactable = true;

	//TEXT
	meshList[SP2::GEO_TIMEDISPLAY] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_TIMEDISPLAY]->textureID = LoadTGA("Image//calibri.tga");
	meshList[SP2::GEO_JETPACKUI] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_JETPACKUI]->textureID = LoadTGA("Image//calibri.tga");
	meshList[SP2::GEO_TIME] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_TIME]->textureID = LoadTGA("Image//calibri.tga");
	meshList[SP2::GEO_ENEMYHEALTH] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_ENEMYHEALTH]->textureID = LoadTGA("Image//calibri.tga");
	meshList[SP2::GEO_ENEMYHEALTHDISPLAY] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_ENEMYHEALTHDISPLAY]->textureID = LoadTGA("Image//calibri.tga");
	meshList[SP2::GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[SP2::GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
}
