//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CLevel.cpp
// Description	:	main implementation for CLevel
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //
#include <vector>
// Local Includes //
#include "CPlayer.h"
#include "CInterface.h"
#include "TextLabel.h"
#include "CubeMap.h"
#include "Model.h"
#include "ModelMesh.h"
// This Includes //
#include "CLevel.h"
#include "Utils.h"
#include <glm\gtx\string_cast.hpp>

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;

// Constructor //
CLevel::CLevel()
{

}

// Destructor //
CLevel::~CLevel()
{
	
}

void CLevel::addPlayer()
{
	//Creating Player
	CharacterSpr = make_shared<CPlayer>();
	CharacterSpr->initModel("Resources/Models/Tank/Tank.obj", CUtility::BPModelProgram);
	CharacterSpr->init(5.0f, 10.0f);	//Sets Move speed and jumpheight
	CharacterSpr->objPosition = { 0.0f,50.0f,0.0f };	//sets the players spawning locatin
	CharacterSpr->objScale = { 10.0f, 10.0f, 10.0f };	//sets their scale
	CharacterSpr->objRotate = { 90.0f, 90.0f, 0.0f };
	SpritesAdd(CharacterSpr);							//Adds to the spr vector
	CharacterSpr->iObjectMechanicsType = CUtility::PLAYER;
}


void CLevel::addEnemy()
{
	std::shared_ptr<CEnemy>SlimeSpr;
	for (int i = 0; i < 15; i++)
	{
		SlimeSpr = make_shared<CEnemy>();
		SlimeSpr->init3D("Resources/enemies/slime0.png", 0.0f, 0.0f, 0);
		SlimeSpr->init(2.0f, 2.0f);						//Sets Move speed and jumpheight
		SlimeSpr->objPosition = { 0.0f, 0.0f + (10.0f* i),0.0f }; //Sets the enemy position
		SpritesAdd(SlimeSpr);							//Adds to Sprite vector
		v_CollisionObjects.push_back(SlimeSpr);					//Adds to enemy vector to keep track of enemies
		v_Enemies.push_back(SlimeSpr);
		SlimeSpr->iObjectMechanicsType = CUtility::ENEMY;
	}
	std::shared_ptr<CSprite>ObstacleSpr;
	ObstacleSpr = make_shared<CSprite>();
	ObstacleSpr->init3D("Resources/enemies/slime0.png", 0.0f, 0.0f, 0);	
	ObstacleSpr->objPosition = { 100.0f, 100.0f,0.0f };				
	ObstacleSpr->objScale = { 3.0f,3.0f,3.0f };
	SpritesAdd(ObstacleSpr);											
	ObstacleSpr->iObjectMechanicsType = CUtility::IMOBIL_WALL;
	v_CollisionObjects.push_back(SlimeSpr);
}

void CLevel::addLevel()
{
	std::shared_ptr<CSprite>BackGroundSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>EntranceSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>ExitSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>Sphere = make_shared<CSprite>();

	Sphere->init3D("Resources/entrance.png", 0.0, 0.0, 2);
	Sphere->objPosition = { 0.0f, 0.0f,0.0f };
	Sphere->objScale = { 20.0f,20.0f,20.0f };
	//loads sprites for the different objects in level
	BackGroundSpr->init3D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	EntranceSpr->init3D("Resources/entrance.png", 0.0, 0.0, 0);
	ExitSpr->init3D("Resources/exit.png", 0.0, 0.0, 0);

	EndSpr = ExitSpr;
	BackGroundSpr->objPosition = { 0.0f, 0.0f, -200.0f };	//its position in the world space
	//BackGroundSpr->objScale = { 30.0f, 30.0f, 30.0f };
	//BackGroundSpr->objScale = { 5.0f,2.5f,1.0f};
	EntranceSpr->objPosition = { -550.0f, -195.0f, 1.0f }; //its position in the world space
	ExitSpr->objPosition = { 550.0f,-195.0f,1.0f }; //its position in the world space
	//adding them to spr vec
	SpritesAdd(BackGroundSpr);
	SpritesAdd(EntranceSpr);
	SpritesAdd(ExitSpr);
	SpritesAdd(Sphere);
}

void CLevel::addMenu()
{
	std::shared_ptr<CSprite> MenuSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite> startBtn0 = make_shared<CSprite>();

	MenuSpr->init3D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	startBtn0->init3D("Resources/start0.png", 0.0, 0.0, 0);

	MenuSpr->objPosition = { 0.0f, 0.0f, -200.0f };
	startBtn0->objPosition = { 0.0f, 0.0f, -150.0f };

	SpritesAdd(MenuSpr);
	SpritesAdd(startBtn0);
}

void CLevel::addCubeMap()
{
	//Storing the correct order of file paths
	std::vector<std::string> cubemapPaths =
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"back.jpg",
		"front.jpg"
	};
	m_cubemap = new CCubeMap(cubemapPaths);
}

void CLevel::addModels()
{
	//std::shared_ptr<CSprite>Model3D = make_shared<CSprite>();
	//Model3D->initModel("Resources/Models/Tank/Tank.obj", CUtility::modelProgram);
	//SpritesAdd(Model3D);
	//Model3D->objPosition = { -400.0f, 200.0f, 0.0f };
	//Model3D->objRotate = { 90.0f, 90.0f, 0.0f };
	//Model3D->objScale = { 30.0f, 30.0f, 30.0f };

	//std::shared_ptr<CSprite>Model3D3 = make_shared<CSprite>();
	//Model3D3->initModel("Resources/Models/nanosuit/nanosuit.obj", CUtility::modelProgram);
	//SpritesAdd(Model3D3);
	//Model3D3->objPosition = { -400.0f, 100.0f, 0.0f };
	//Model3D3->objRotate = { 90.0f, 90.0f, 0.0f };
	//Model3D3->objScale = { 30.0f, 30.0f, 30.0f };

	//std::shared_ptr<CSprite>Model3D4 = make_shared<CSprite>();
	//Model3D4->initModel("Resources/Models/pug/Dog 1.obj", CUtility::modelProgram);
	//SpritesAdd(Model3D4);
	//Model3D4->objPosition = { -400.0f, 50.0f, 0.0f };
	//Model3D4->objRotate = { 90.0f, 90.0f, 0.0f };
	//Model3D4->objScale = { 30.0f, 30.0f, 30.0f };

	//std::shared_ptr<CSprite>model3d5 = make_shared<CSprite>();
	//model3d5->initModel("resources/models/pugenemy/Dog 1.obj", CUtility::modelProgram);
	//SpritesAdd(model3d5);
	//model3d5->objPosition = { -400.0f, 0.0f, 0.0f };
	//model3d5->objRotate = { 90.0f, 90.0f, 0.0f };
	//model3d5->objScale = { 30.0f, 30.0f, 30.0f };
}

void CLevel::addEndMenu()
{
	std::shared_ptr<CSprite> EndSpr = make_shared<CSprite>();
	EndSpr->init3D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	SpritesAdd(EndSpr);
}

void CLevel::render()
{
	m_cubemap->render();	//calls render function of cubemap

	CScene::render();		//calls scene render which goes through the spritevector and renders everything
}

void CLevel::update()
{
	float fDotProduct = glm::dot(CControls::GetInstance()->ray_world, normal);
	float fDistance;
	if (fDotProduct == 0)
	{
		MousePointPos = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		fDistance = -(glm::dot(CCamera::GetInstance()->m_v3CameraPos, normal) / glm::dot(CControls::GetInstance()->ray_world, normal));
		MousePointPos = CCamera::GetInstance()->m_v3CameraPos + (fDistance * CControls::GetInstance()->ray_world);
	}
	
	if (CharacterSpr != nullptr)
	{
		CharacterSpr->LookAt(MousePointPos);
	}
	CScene::update();

	for (auto it : v_Enemies)
	{
		if (CharacterSpr != nullptr)
		{
			it->update(*CharacterSpr,&v_CollisionObjects);
		}
	}
	/*
	if (CControls::GetInstance()->cKeyState[32] == CControls::INPUT_FIRST_PRESSED && (abs(CharacterSpr->objPosition.x - EndSpr->objPosition.x) < 30) && abs(CharacterSpr->objPosition.y - EndSpr->objPosition.y) < 30 && v_Enemies.empty())
	{
		resetLevel();
		CSceneManager::GetInstance()->switchScene(CSceneManager::END);
	}*/
}

void CLevel::resetLevel()
{
	//Checks if the enemy vector is empty or not, if not empty goes through and deletes the enemy 
	if (!v_Enemies.empty())
	{
		for (auto it : v_Enemies)
		{
			delEnemy(it);
		}
		
	}
	//adds the enemy again
	addEnemy();
	//deletes the sprite
	DeleteSprite(CharacterSpr);
	//adds the player again
	addPlayer();
	//resets the score
	nScore = 0;

}

void CLevel::delEnemy(std::shared_ptr<CEnemy>TobeDeleted)
{
	for (auto it = v_Enemies.begin(); it != v_Enemies.end(); it++)
	{
		if ((*it) == TobeDeleted)
		{
			v_Enemies.erase(it);
			DeleteSprite(TobeDeleted);
			break;
		}

	}
}

