//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CGameMech.h
// Description	:	header file outlining the CGameMech
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CGAMEMECH_H__
#define _CGAMEMECH_H__

// Library Includes //
#include <memory>
// Local Includes //
#include "CSprite.h"
#include "CPlayer.h"
#include "CEnemy.h"


class CGameMech
{
    // Member Functions //
        public:
            CGameMech();
            ~CGameMech();
			//Checks the collision between the player and enemy
			static bool bIsDetectingCollision(std::shared_ptr<CSprite> _pObj1, std::shared_ptr<CSprite> _pObj2, glm::vec2 _v2SprMovement);//Vec2 for 2D game

        private:
};

#endif // _CGAMEMECH_H__

