#include "Coins.h"
#include "MeshBuilder.h"
#include "GL\glew.h"
#include "LoadTGA.h"
void coins::init()
{
	Vector3 coordinates[47]
	{
			Vector3(15, 7, -230),
			Vector3(10, 7, -130),
			Vector3(25, 27, -50),
			Vector3(15, 7, 0),
			Vector3(32, 17, 30),
			Vector3(7, 17, 80),
			Vector3(32, 17, 100),
			Vector3(5, 7, 175),
			Vector3(25, 7, 230),
			Vector3(-17, 7, 240),
			Vector3(-17, 7, 140),
			Vector3(-17, 7, -30),
			Vector3(-30, 27, -80),
			Vector3(-10, 27, -120),
			Vector3(-14, 7, -190),
			Vector3(0, 257, -425),
			Vector3(10, 257, -385),
			Vector3(-10, 257, -345),
			Vector3(0, 257, -305),
			Vector3(0, 257, -225),
			Vector3(-10, 257, -185),
			Vector3(0, 257, -145),
			Vector3(10, 257, -105),
			Vector3(-10, 257, -65),
			Vector3(0, 257, -25),
			Vector3(0, 257, 55),
			Vector3(10, 257, 95),
			Vector3(-10, 257, 135),
			Vector3(0, 257, 175),
			Vector3(-10, 257, 215),
			Vector3(0, 257, 255),
			Vector3(10, 257, 295),
			Vector3(0, 257, 335),
			Vector3(-10, 257, 385),
			Vector3(160, -497, -210),
			Vector3(170, -497, -115),
			Vector3(110, -497, -35),
			Vector3(165, -497, 10),
			Vector3(110, -497, 65),
			Vector3(-70, -497, 90),
			Vector3(-180, -497, 125),
			Vector3(-170, -497, 25),
			Vector3(-115, -497, 5),
			Vector3(-30, -497, 5),
			Vector3(0, -497, 25),
			Vector3(25, -497, 0),
			Vector3(0, -497, 30),

	};
	for (int i = 0; i < 47; ++i)
	{
		Mesh *temp;
		temp = MeshBuilder::GenerateOBJ("coin", "OBJ//coin.obj");
		temp->position = coordinates[i];
		temp->min = nullptr;
		temp->max = nullptr;
		temp->textureID = LoadTGA("Image//coinUV.tga");
		allCoins.push_back(temp);
	}
	return;
}

void coins::pickup(Camera5 camera)
{
	int offset = 1;
	for (int i = 0; i < allCoins.size(); ++i)
	{
		if (
			camera.position.x > allCoins[i]->Pmin->x - offset + allCoins[i]->position.x &&
			camera.position.x < allCoins[i]->Pmax->x + offset + allCoins[i]->position.x &&
			camera.position.y > allCoins[i]->Pmin->y - offset + allCoins[i]->position.y &&
			camera.position.y < allCoins[i]->Pmax->y + offset + allCoins[i]->position.y &&
			camera.position.z > allCoins[i]->Pmin->z - offset + allCoins[i]->position.z &&
			camera.position.z < allCoins[i]->Pmax->z + offset + allCoins[i]->position.z
			)
		{
			acquired++;
			allCoins.erase(allCoins.begin() + i);
			break;
		}
	}
}