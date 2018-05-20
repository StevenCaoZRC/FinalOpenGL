//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CEnemy.h
// Description	:	header file outlining the CEnemy
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CENEMY_H__
#define _CENEMY_H__

// Library Includes //

// Local Includes //
#include "CSprite.h"
#include "CSceneManager.h"
// Types //

// Constants //

// Prototypes //

class CEnemy : public CSprite
{
    // Member Functions //
        public:
            CEnemy(const char* _fileName, float fWidth, float fHeight);
            ~CEnemy();
			float fJumpHeight;
			float fMoveSpeed;
			void init(float _fMoveSpeed, float _fJumpHeight);
			void update();
			bool bIsAlive = true;
			bool bIsGoingRight = true;
        private:

};

#endif // _CENEMY_H__

