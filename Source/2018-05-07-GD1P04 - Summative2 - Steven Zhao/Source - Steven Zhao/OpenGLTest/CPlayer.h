//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CPlayer.h
// Description	:	header file outlining the CPlayer
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CPLAYER_H__
#define _CPLAYER_H__

// Library Includes //

// Local Includes //
#include "CSprite.h"
#include "CControls.h"
#include "CScene.h"
#include "CGameMech.h"
// Types //

// Constants //

// Prototypes //

class CPlayer : public CSprite
{

public:
    CPlayer();
    ~CPlayer();
	float fMovementSpeed;
	float fJumpHeight;
	float fGravity;
	glm::vec2 v2_Movement = glm::vec2();
	void init(float _fMovementSpeed, float _fJumpHeight);
	void update();
	bool bIsPlayerAlive = true;
	
};

#endif // _CPLAYER_H__

