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
	CharacterSpr = make_shared<CPlayer>("Resources/player_character/character_idle_1.png", 0.0f, 0.0f);
	CharacterSpr->init(5.0f, 10.0f);
	CharacterSpr->addFrame("Resources/player_character/character_jump_0.png");
	CharacterSpr->objPosition = { -550.0f,-215.0f,0.0f };
	SpritesAdd(CharacterSpr);
}

void CLevel::addEnemy()
{
	//Creating Enemy1
	std::shared_ptr<CEnemy>SlimeSpr = make_shared<CEnemy>("Resources/enemies/slime0.png", 0.0f, 0.0f);
	SlimeSpr->init(2.0f,2.0f);
	SlimeSpr->objPosition = { 0.0f,-224.0f,0.0f };
	SpritesAdd(SlimeSpr);
	v_Enemies.push_back(SlimeSpr);
}

void CLevel::render()
{
	CScene::render();

}

void CLevel::update()
{
	CScene::update();
	
	if (CControls::InstanceGet()->cKeyState[32] == CControls::INPUT_FIRST_PRESSED && (abs(CharacterSpr->objPosition.x - EndSpr->objPosition.x) < 30) && abs(CharacterSpr->objPosition.y - EndSpr->objPosition.y) < 30 && v_Enemies.empty())
	{
		resetLevel();
		CSceneManager::InstanceGet()->switchScene(CSceneManager::END);
	}
	
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

