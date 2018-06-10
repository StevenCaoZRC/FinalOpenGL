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
#include "CProjectile.h"
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
	m_bPlayerAlive = true;
	//Creating Player
	CharacterSpr = make_shared<CPlayer>();
	CharacterSpr->initModel("Resources/Models/Ship/Sample_Ship.obj", CUtility::BPModelProgram, 10.0f);
	CharacterSpr->init(5.0f, 10.0f);	//Sets Move speed and jumpheight
	CharacterSpr->objPosition = { -400.0f,-200.0f,0.0f };	//sets the players spawning locatin
	CharacterSpr->objScale = { 50.0f, 50.0f, 50.0f };	//sets their scale
	CharacterSpr->objRotate = { 90.0f, 90.0f, 0.0f };
	SpritesAdd(CharacterSpr);							//Adds to the spr vector
	CharacterSpr->iObjectMechanicsType = CUtility::PLAYER;
	v_CollisionObjects.push_back(CharacterSpr);
}


void CLevel::addEnemy(int _iCount)
{
	std::shared_ptr<CEnemy>SlimeSpr;
	for (int i = 0; i < _iCount; i++)
	{
		SlimeSpr = make_shared<CEnemy>();
		SlimeSpr->initModel("Resources/Models/pug/Dog 1.obj", CUtility::BPModelProgram, 10.0f);
		SlimeSpr->init(2.0f, 2.0f, 10);						//Sets Move speed and jumpheight
		SlimeSpr->objPosition = { 0.0f, 0.0f + (10.0f* i),0.0f }; //Sets the enemy position
		SlimeSpr->objScale = { 10.0f, 10.0f, 10.0f };	//sets their scale
		SlimeSpr->objRotate = { 90.0f, 90.0f, 0.0f };
		SpritesAdd(SlimeSpr);							//Adds to Sprite vector
		v_CollisionObjects.push_back(SlimeSpr);					//Adds to enemy vector to keep track of enemies
		v_Enemies.push_back(SlimeSpr);
		SlimeSpr->iObjectMechanicsType = CUtility::ENEMY;
	}
	//std::shared_ptr<CSprite>ObstacleSpr;
	//ObstacleSpr = make_shared<CSprite>();
	//ObstacleSpr->init3D("Resources/enemies/slime0.png", 0.0f, 0.0f, 0);	
	//ObstacleSpr->objPosition = { 100.0f, 100.0f,0.0f };				
	//ObstacleSpr->ScaleSprite(3.0f);
	//SpritesAdd(ObstacleSpr);											
	//ObstacleSpr->iObjectMechanicsType = CUtility::IMOBIL_WALL;
	//v_CollisionObjects.push_back(ObstacleSpr);
}

void CLevel::addLevel()
{
	m_iCurLevel = 1;
	std::shared_ptr<CSprite>BackGroundSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>EntranceSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>ExitSpr = make_shared<CSprite>();
	std::shared_ptr<CSprite>ReflectSpr = make_shared<CSprite>();

	//loads sprites for the different objects in level

	BackGroundSpr->init3D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	EntranceSpr->init3D("Resources/entrance.png", 0.0, 0.0, 0);
	ExitSpr->init3D("Resources/exit.png", 0.0, 0.0, 0);
	ReflectSpr->init3D("Resources/entrance.png",0.0,0.0,2);
	EndSpr = ExitSpr;
	BackGroundSpr->objPosition = { 0.0f, 0.0f, -200.0f };	//its position in the world space
	//BackGroundSpr->objScale = { 30.0f, 30.0f, 30.0f };
	//BackGroundSpr->objScale = { 5.0f,2.5f,1.0f};
	EntranceSpr->objPosition = { -550.0f, -195.0f, 1.0f }; //its position in the world space
	ExitSpr->objPosition = { 550.0f,-195.0f,1.0f }; //its position in the world space
	ReflectSpr->objPosition = { 0.0f,0.0f,0.0f };
	ReflectSpr->objScale = { 30.0f,30.0f,30.0f };
	ReflectSpr->objRotate = { 270.0f,0.0f,0.0f };
	//adding them to spr vec
	SpritesAdd(BackGroundSpr);
	SpritesAdd(EntranceSpr);
	SpritesAdd(ExitSpr);
	//SpritesAdd(ReflectSpr);
}

void CLevel::addMenu()
{
	
	//std::shared_ptr<CSprite> MenuSpr = make_shared<CSprite>();
	startBtn0 = make_shared<CSprite>();
	startBtn1 = make_shared<CSprite>();
	startBtn2 = make_shared<CSprite>();
	startBtn3 = make_shared<CSprite>();

	//MenuSpr->init2D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT);
	startBtn0->init2D("Resources/Menu Buttons/Single Player Blue.png", 0.0, 0.0);
	startBtn1->init2D("Resources/Menu Buttons/Controls Blue.png", 0.0, 0.0);
	startBtn2->init2D("Resources/Menu Buttons/Options Blue.png", 0.0, 0.0);
	startBtn3->init2D("Resources/Menu Buttons/Exit Blue.png", 0.0, 0.0);

	//MenuSpr->objPosition = { 0.0f, 0.0f, 0.0f };
	startBtn0->objPosition = { 0.0f, 120.0f, 1.0f };
	startBtn1->objPosition = { 0.0f, 50.0f, 1.0f };
	startBtn2->objPosition = { 0.0f, -20.0f, 1.0f };
	startBtn3->objPosition = { 0.0f, -90.0f, 1.0f };

	//SpritesAdd(MenuSpr);
	SpritesAdd(startBtn0);
	SpritesAdd(startBtn1);
	SpritesAdd(startBtn2);
	SpritesAdd(startBtn3);
}

void CLevel::addCubeMap()
{
	//Storing the correct order of file paths
	std::vector<std::string> cubemapPaths =
	{
		"right.png",
		"left.png",
		"up.png",
		"down.png",
		"back.png",
		"front.png"
	};
	m_cubemap = new CCubeMap(cubemapPaths);
	m_cubemap->objRotate = { 90.0f,0.0f,0.0f };
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

	//std::shared_ptr<CSprite> EndSpr = make_shared<CSprite>();
	//EndSpr->init3D("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	//SpritesAdd(EndSpr);
	std::shared_ptr<CSprite> EndBtn0 = make_shared<CSprite>();
	EndBtn0->init2D("Resources/Menu Buttons/Main Menu Blue.png", 0.0, 0.0);
	EndBtn0->objPosition = { 0.0f, -120.0f, 1.0f };
	SpritesAdd(EndBtn0);
}

void CLevel::render()
{
	m_cubemap->render();	//calls render function of cubemap

	CScene::render();		//calls scene render which goes through the spritevector and renders everything
}

void CLevel::update()
{
	if (m_iShootCD > 0)
	{
		m_iShootCD--;
	}
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
 		if ((CControls::GetInstance()->cMouse[0] == CControls::INPUT_HOLD || CControls::GetInstance()->cMouse[0] == CControls::INPUT_FIRST_RELEASE) && m_iShootCD == 0)
		{
			m_iShootCD = 20;
			std::shared_ptr<CProjectile> aBullet = make_shared<CProjectile>();
			aBullet->init3D("Resources/blue.png", 5.0f,5.0f, 1);
			aBullet->ScaleSprite(2.0f);
			aBullet->objPosition = {CharacterSpr->objPosition};
			aBullet->m_iDamage = 10;
			aBullet->m_CurrentVelo = glm::normalize(MousePointPos - CharacterSpr->objPosition) * 5.0f;
			v_ProjectileObjects.push_back(aBullet);
			v_CollisionObjects.push_back(aBullet);
			SpritesAdd(aBullet);
			aBullet->m_iProjectileType = CUtility::MY_PROJ;
			aBullet->iObjectMechanicsType = CUtility::MY_PROJ;
		}
	}
	CScene::update();

	for (auto it : v_Enemies)
	{
		if (CharacterSpr != nullptr)
		{
			it->update(*CharacterSpr,&v_CollisionObjects);
		}
	}
	for (auto it : v_ProjectileObjects)
	{
		it->update(*CharacterSpr, &v_CollisionObjects);
	}

	delProjectile();
	delEnemy();
	delPlayer();
	LevelUp();
	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::LEVEL)
	{
		if (CharacterSpr == nullptr)
		{
			CSceneManager::GetInstance()->switchScene(CSceneManager::END);
			resetLevel();
		}
	}
	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::MENU)
	{
		float Left = startBtn0->objPosition.x - startBtn0->nWidth / 2;
		float Right = startBtn0->objPosition.x + startBtn0->nWidth / 2;
		float Top = startBtn0->objPosition.y + startBtn0->nHeight / 2;
		float Bot = startBtn0->objPosition.y - startBtn0->nHeight / 2;
		if (MousePointPos.x >= Left && MousePointPos.x <= Right && MousePointPos.y <= Top && MousePointPos.y >= Bot)
		{
			startBtn0->addFrame("Resources/Menu Buttons/Single Player Green.png");
			if (CControls::GetInstance()->cMouse[0] == CControls::INPUT_HOLD || CControls::GetInstance()->cMouse[0] == CControls::INPUT_FIRST_RELEASE)
			{
				CSceneManager::GetInstance()->switchScene(CSceneManager::LEVEL);
			}
		}
		Left = startBtn1->objPosition.x - startBtn1->nWidth / 2;
		Right = startBtn1->objPosition.x + startBtn1->nWidth / 2;
		Top = startBtn1->objPosition.y + startBtn1->nHeight / 2;
		Bot = startBtn1->objPosition.y - startBtn1->nHeight / 2;
		if (MousePointPos.x >= Left && MousePointPos.x <= Right && MousePointPos.y <= Top && MousePointPos.y >= Bot)
		{

		}
		Left = startBtn2->objPosition.x - startBtn2->nWidth / 2;
		Right = startBtn2->objPosition.x + startBtn2->nWidth / 2;
		Top = startBtn2->objPosition.y + startBtn2->nHeight / 2;
		Bot = startBtn2->objPosition.y - startBtn2->nHeight / 2;
		if (MousePointPos.x >= Left && MousePointPos.x <= Right && MousePointPos.y <= Top && MousePointPos.y >= Bot)
		{

		}
		Left = startBtn3->objPosition.x - startBtn3->nWidth / 2;
		Right = startBtn3->objPosition.x + startBtn3->nWidth / 2;
		Top = startBtn3->objPosition.y + startBtn3->nHeight / 2;
		Bot = startBtn3->objPosition.y - startBtn3->nHeight / 2;
		if (MousePointPos.x >= Left && MousePointPos.x <= Right && MousePointPos.y <= Top && MousePointPos.y >= Bot)
		{

		}
	}
	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::END
)
	{

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
	while (v_Enemies.size() > 0)
	{
		DeleteSprite(v_Enemies.at(0));
		DeleteCollision(dynamic_pointer_cast<CSprite>(v_Enemies.at(0)));
		v_Enemies.erase(v_Enemies.begin() + 0);
	}
	addModels();
	addEnemy(15);
	addPlayer();
	m_iCurLevel = 1;
}

void CLevel::delEnemy()
{
	for (int i = 0; i < v_Enemies.size(); i++)
	{
		if (v_Enemies.at(i)->m_iHealth <= 0)
		{
			DeleteSprite(v_Enemies.at(i));
			DeleteCollision(dynamic_pointer_cast<CSprite>(v_Enemies.at(i)));
			v_Enemies.erase(v_Enemies.begin() + i);
			CInterface::GetInstance()->iScore+= 1;
		}
	}

}

void CLevel::delProjectile()
{
	for (int i = 0; i < v_ProjectileObjects.size(); i++)
	{
		if (v_ProjectileObjects.at(i)->m_iAliveTime > 300)
		{
			DeleteSprite(v_ProjectileObjects.at(i));
			DeleteCollision(dynamic_pointer_cast<CSprite>(v_ProjectileObjects.at(i)));
			v_ProjectileObjects.erase(v_ProjectileObjects.begin() + i);
		}
	}
}

void CLevel::delPlayer()
{
	std::shared_ptr<CLevel>Level = std::dynamic_pointer_cast<CLevel>(CSceneManager::GetInstance()->GetCurrentScene());
	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::LEVEL)
	{
		if (m_bPlayerAlive == true)
		{
			if (CharacterSpr->m_iHealth <= 0)
			{
				m_bPlayerAlive = false;
				DeleteSprite(CharacterSpr);
				DeleteCollision(CharacterSpr);
				CharacterSpr = nullptr;
			}
		}
	}
}



void CLevel::DeleteCollision(std::shared_ptr<CSprite> TobeDeleted)
{
	//goes through and finds all the sprites that will be deleted and delete them
	//decides what needs to be deleted by the parameter passed in, a sharedptr of sprite
	for (auto it = v_CollisionObjects.begin(); it != v_CollisionObjects.end(); it++)
	{
		if ((*it) == TobeDeleted)
		{
			v_CollisionObjects.erase(it);
			break;
		}

	}
}

void CLevel::LevelUp()
{
	std::shared_ptr<CLevel>Level = std::dynamic_pointer_cast<CLevel>(CSceneManager::GetInstance()->GetCurrentScene());
	if(v_Enemies.size() == 0 && CSceneManager::GetInstance()->nCurrentScene == CSceneManager::LEVEL)
	{
		m_iCurLevel++;
		addEnemy(15 * m_iCurLevel);
	}
}

