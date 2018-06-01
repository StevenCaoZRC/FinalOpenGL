//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CPlayer.cpp
// Description	:	main implementation for CPlayer
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //
#include "CInterface.h"
#include "CSound.h"
// This Includes //
#include "CPlayer.h"

using namespace std;

// Constructor //
CPlayer::CPlayer(const char* _fileName, float fWidth, float fHeight)
	:  CSprite(_fileName, fWidth, fHeight)
{

}

// Destructor //
CPlayer::~CPlayer()
{

}

void CPlayer::init(float _fMovementSpeed, float _fJumpHeight)
{
	fMovementSpeed = _fMovementSpeed;
	fJumpHeight = _fJumpHeight;
	fGravity = 0.5f;
	//---------------|Sound Stuff|---------------//
	CSound::GetInstance()->init();
	CSound::GetInstance()->addSound();
	CSound::GetInstance()->soundMgr->playSound(CSound::GetInstance()->bgMusic, 0, false, &CSound::GetInstance()->BgMusicChannel);\
	CSound::GetInstance()->soundEffects->setVolume(0.1f);
}

void CPlayer::update()
{
	//Casting current level scene to dirived type CLevel, if it is not Clevel will return nullptr
	std::shared_ptr<CLevel>RefrenceLevel = std::dynamic_pointer_cast<CLevel>(CSceneManager::GetInstance()->GetCurrentScene());
	if (!RefrenceLevel)
	{
		return; //if the scene is not a level
	}

	//LEVEL BOUNDARYS
	//BOTTOM
	if (objPosition.y + fMovementSpeed <-((float)Utility::SCR_HEIGHT / 2) + 150.0f)
	{
		objPosition.y = -((float)Utility::SCR_HEIGHT / 2) + 150.0f;
		v2_Movement.y = 0;
	}
	//LEFT
	if (objPosition.x - fMovementSpeed < -((float)Utility::SCR_WIDTH / 2) + 150.0f)
	{
		objPosition.x = -((float)Utility::SCR_WIDTH / 2) + 150.0f;
		v2_Movement.x = 0;
	}
	//TOP
	if (objPosition.y + fMovementSpeed > ((float)Utility::SCR_HEIGHT / 2) - 150.0f)
	{
		objPosition.y = ((float)Utility::SCR_HEIGHT / 2) - 150.0f;
		v2_Movement.y = 0;
	}
	//RIGHT
	if (objPosition.x + fMovementSpeed > ((float)Utility::SCR_WIDTH / 2) - 150.0f)
	{
		objPosition.x = ((float)Utility::SCR_WIDTH / 2) - 150.0f;
		v2_Movement.x = 0;
	}

	//COMMAND INPUTS 8 DIRECTIONAL

	//UP
	if (CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.y = +fMovementSpeed;
	}
	//DOWN
	else if (CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.y = -fMovementSpeed;
	}
	//RIGHT
	if(CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.x = +fMovementSpeed;
		objScale.x = 1;
	}
	//LEFT
	else if (CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.x = -fMovementSpeed;
		objScale.x = -1;
	}
	//RITGHT UP
	if (CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.x = +fMovementSpeed / 1.414213f;
		v2_Movement.y = +fMovementSpeed / 1.414213f;
		objScale.x = 1;
	}
	//RIGHT DOWN
	else if(CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_HOLD)
	{
		v2_Movement.x = +fMovementSpeed / 1.414213f;
		v2_Movement.y = -fMovementSpeed / 1.414213f;
		objScale.x = 1;
	}
	//LEFT DOWN
	if (CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.x = -fMovementSpeed / 1.414213f;
		v2_Movement.y = +fMovementSpeed / 1.414213f;
		objScale.x = -1;
	}
	//LEFT UP
	else if (CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_HOLD
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_HOLD)
	{
		v2_Movement.x = -fMovementSpeed / 1.414213f;
		v2_Movement.y = -fMovementSpeed / 1.414213f;
		objScale.x = -1;
	}
	//IF NO HORIZONTAL MOVEMENT
	if (CControls::GetInstance()->cKeyState[(unsigned char)'a'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'d'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.x = 0;
	}
	//IF NO VERTICAL MOVEMENT
	if (CControls::GetInstance()->cKeyState[(unsigned char)'w'] == CControls::INPUT_RELEASED
		&& CControls::GetInstance()->cKeyState[(unsigned char)'s'] == CControls::INPUT_RELEASED)
	{
		v2_Movement.y = 0;
	}

	for (auto it : RefrenceLevel->v_Enemies) //Refrence level is current level
	{
		if (CGameMech::bIsDetectingCollision(this->shared_from_this(), it, v2_Movement))
		{
			if (this->shared_from_this()->objPosition.x + this->shared_from_this()->nWidth + v2_Movement.x > it->objPosition.x &&
				this->shared_from_this()->objPosition.x + v2_Movement.x < it->objPosition.x + it->nWidth)
			{
				it->bIsAlive = false;
				RefrenceLevel->delEnemy(it);
				CSound::GetInstance()->soundMgr->playSound(CSound::GetInstance()->sfx, 0, false, &CSound::GetInstance()->soundEffects);
				CSound::GetInstance()->soundEffects->setVolume(0.6f);
				RefrenceLevel->nScore += 10;
				CInterface::CInterface::GetInstance()->bWon = true;
				
				return;
			}

			bIsPlayerAlive = false;
			CSound::GetInstance()->soundMgr->playSound(CSound::GetInstance()->sfx, 0, false, &CSound::GetInstance()->soundEffects);
			CSound::GetInstance()->soundEffects->setVolume(0.6f);
			RefrenceLevel->DeleteSprite(this->shared_from_this());
			if (CSceneManager::GetInstance()->nCurrentScene = CSceneManager::LEVEL && bIsPlayerAlive == false)
			{
				RefrenceLevel->delEnemy(it);
				RefrenceLevel->DeleteSprite(RefrenceLevel->CharacterSpr);
				RefrenceLevel->addEnemy();
				RefrenceLevel->addPlayer();
				RefrenceLevel->nScore = 0;
				CSceneManager::GetInstance()->nCurrentScene = CSceneManager::END;
				CInterface::CInterface::GetInstance()->bWon = false;
				
			}
			
		}	
		
	}
	//CSound::GetInstance()->soundMgr->playSound(CSound::GetInstance()->bgMusic, 0, false, &CSound::GetInstance()->BgMusicChannel);

	
	objPosition += glm::vec3(v2_Movement,0); 
}

