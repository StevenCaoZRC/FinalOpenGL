//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CEnemy.cpp
// Description	:	main implementation for CEnemy
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //

// This Includes //
#include "CEnemy.h"

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;

// Constructor //
CEnemy::CEnemy(const char * _fileName, float fWidth, float fHeight):CSprite(_fileName, fWidth, fHeight)
{
}

// Destructor //
CEnemy::~CEnemy()
{

}

void CEnemy::init(float _fMoveSpeed, float _fJumpHeight)
{
	fMoveSpeed = _fMoveSpeed;
	fJumpHeight = _fJumpHeight;
}

void CEnemy::update()
{
	if (bIsAlive)
	{
		if (bIsGoingRight)
		{
			objPosition.x += fMoveSpeed;
			objScale.x = -1;
			if (objPosition.x >=250)
				bIsGoingRight = false;
		}
		else if (bIsGoingRight == false)
		{
			objPosition.x -= fMoveSpeed;
			objScale.x = 1;
			if (objPosition.x <= -250)
				bIsGoingRight = true;
		}
		
		
	}
}

