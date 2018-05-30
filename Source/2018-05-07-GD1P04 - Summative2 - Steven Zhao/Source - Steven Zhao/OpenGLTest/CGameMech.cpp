//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CGameMech.cpp
// Description	:	main implementation for CGameMech
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //

// This Includes //
#include "CGameMech.h"

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;

// Constructor //
CGameMech::CGameMech()
{

}

// Destructor //
CGameMech::~CGameMech()
{

}

bool CGameMech::bIsDetectingCollision(std::shared_ptr<CSprite> _pObj1, std::shared_ptr<CSprite> _pObj2, glm::vec2 _v2SprMovement)
{
	//Since spr are centered, it is only the distance from the center of the spr to the out side. Created for convience
	float fObj1W = (float)_pObj1->nWidth - 10;
	float fObj1H = (float)_pObj1->nHeight;
	float fObj2W = (float)_pObj2->nWidth - 10;
	float fObj2H = (float)_pObj2->nHeight;
	//Obj1 Positions 
	float fObj1Right = _pObj1->objPosition.x + fObj1W + _v2SprMovement.x;
	float fObj1Left = _pObj1->objPosition.x - fObj1W + _v2SprMovement.x;
	float fObj1Up = _pObj1->objPosition.y + fObj1H + _v2SprMovement.y;
	float fObj1Down = _pObj1->objPosition.y - fObj1H + _v2SprMovement.y;

	//Obj2 Positions (The one checking against)
	float fObj2Right = _pObj2->objPosition.x + fObj2W;
	float fObj2Left = _pObj2->objPosition.x - fObj2W;
	float fObj2Up = _pObj2->objPosition.y + fObj2H;
	float fObj2Down = _pObj2->objPosition.y - fObj2H;
	//Checking if they are colliding
	if (fObj1Right > fObj2Left &&  //Checking right side of obj1
		fObj1Left < fObj2Right && //Checking left side of obj1
		fObj1Up > fObj2Down &&	//Checking above obj1
		fObj1Down < fObj2Up)	//Checking below obj1
		return true;
	return false;
}



