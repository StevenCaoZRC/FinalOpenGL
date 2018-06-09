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

#ifndef _CPROJECTILE_H__
#define _CPROJECTILE_H__

// Library Includes //

// Local Includes //
#include "CSprite.h"
#include "CControls.h"
#include "CScene.h"
#include "CGameMech.h"
// Types //

// Constants //

// Prototypes //

class CProjectile : public CSprite
{
public:
	CProjectile();
	~CProjectile();

	void update(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	void CollisionCheck(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);


	int m_iProjectileType;
	int m_iDamage;
	glm::vec3 m_CurrentVelo;
	int m_iAliveTime;
};


#endif