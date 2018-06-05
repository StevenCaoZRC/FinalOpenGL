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
#include "CEnemy.h"
#include "CInterface.h"
#include "TextLabel.h"

// This Includes //
#include "CLevel.h"

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
	CharacterSpr = make_shared<CPlayer>("Resources/player_character/character_idle_1.png", 0.0f, 0.0f, 1);
	CharacterSpr->init(5.0f, 10.0f);
	CharacterSpr->addFrame("Resources/player_character/character_jump_0.png");
	CharacterSpr->objPosition = { 0.0f,50.0f,0.0f };
	CharacterSpr->objScale = { 30.0f, 30.0f, 10.0f };
	SpritesAdd(CharacterSpr);
}

void CLevel::addEnemy()
{
	//Creating Enemy1
	std::shared_ptr<CEnemy>SlimeSpr = make_shared<CEnemy>("Resources/enemies/slime0.png", 0.0f, 0.0f, 0);
	SlimeSpr->init(2.0f,2.0f);
	SlimeSpr->objPosition = { 100.0f,-50.0f,0.0f };
	//SlimeSpr->objScale = { 0.5f, 0.5f, 0.5f };
	SpritesAdd(SlimeSpr);
	v_Enemies.push_back(SlimeSpr);
}

void CLevel::addLevel()
{
	std::shared_ptr<CSprite>BackGroundSpr = make_shared<CSprite>("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	std::shared_ptr<CSprite>EntranceSpr = make_shared<CSprite>("Resources/entrance.png", 0.0, 0.0, 0);
	std::shared_ptr<CSprite>ExitSpr = make_shared<CSprite>("Resources/exit.png", 0.0, 0.0 , 0);
	EndSpr = ExitSpr;
	BackGroundSpr->objPosition = { 0.0f, 0.0f, -200.0f };
	//BackGroundSpr->objScale = { 30.0f, 30.0f, 30.0f };
	//BackGroundSpr->objScale = { 5.0f,2.5f,1.0f};
	EntranceSpr->objPosition = { -550.0f, -195.0f, 1.0f };
	ExitSpr->objPosition = { 550.0f,-195.0f,1.0f };
	SpritesAdd(BackGroundSpr);
	SpritesAdd(EntranceSpr);
	SpritesAdd(ExitSpr);
}

void CLevel::addMenu()
{
	std::shared_ptr<CSprite> MenuSpr = make_shared<CSprite>("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	std::shared_ptr<CSprite> startBtn0 = make_shared<CSprite>("Resources/start0.png", 0.0, 0.0, 0);
	MenuSpr->objPosition = { 0.0f, 0.0f, -200.0f };
	startBtn0->objPosition = { 0.0f, 0.0f, -150.0f };

	SpritesAdd(MenuSpr);
	SpritesAdd(startBtn0);

}

void CLevel::addEndMenu()
{
	std::shared_ptr<CSprite> EndSpr = make_shared<CSprite>("Resources/dungeon.png", Utility::SCR_WIDTH, Utility::SCR_HEIGHT, 0);
	SpritesAdd(EndSpr);
}

void CLevel::render()
{
	CScene::render();
	
}

void CLevel::update()
{
	CScene::update();

	if (CharacterSpr != nullptr)
	{
		for (auto it : v_Enemies)
		{
			if (CharacterSpr != nullptr)
			{
				it->update(*CharacterSpr);
			}
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
	if (!v_Enemies.empty())
	{
		for (auto it : v_Enemies)
		{
			delEnemy(it);
		}
		
	}
	addEnemy();
	DeleteSprite(CharacterSpr);
	addPlayer();
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

