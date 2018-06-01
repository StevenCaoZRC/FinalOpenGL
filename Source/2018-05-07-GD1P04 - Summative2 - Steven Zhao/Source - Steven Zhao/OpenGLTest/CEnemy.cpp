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
	m_vCurVelocity = { 0.0f, 1000.0f, 0.0f };
}

void CEnemy::update(glm::vec3 _pos)
{
	if (bIsAlive)
	{
		AIFlee(_pos);
	}
	//if (bIsAlive)
	//{
	//	if (bIsGoingRight)
	//	{
	//		objPosition.x += fMoveSpeed;
	//		objScale.x = -1;
	//		if (objPosition.x >=250)
	//			bIsGoingRight = false;
	//	}
	//	else if (bIsGoingRight == false)
	//	{
	//		objPosition.x -= fMoveSpeed;
	//		objScale.x = 1;
	//		if (objPosition.x <= -250)
	//			bIsGoingRight = true;
	//	}
	//	
	//	
	//}
}

void CEnemy::AISeek(glm::vec3 _pos)
{
	//current pos = current position of this item
	glm::vec3 curPos = this->objPosition;
	glm::vec3 seekPos;
	glm::vec3 nextPosSeek;
	glm::vec3 nextPos = objPosition + m_vCurVelocity;
	float steeringratio = 9.0f;
	if (objPosition != _pos) // making sure that you are not right on top of the position your seeking and causing divide by 0 errors
	{

		glm::vec3 v2 = _pos - curPos;
		float v2mag = sqrtf(powf(v2.x, 2) + powf(v2.y, 2) + powf(v2.z, 2));
		if (v2mag > 0.005)
		{
			glm::vec3 v2I = v2 / v2mag;
			nextPosSeek = curPos + (v2I * fMoveSpeed);
		}

		glm::vec3 vSteering = nextPosSeek - nextPos;
		vSteering = vSteering / steeringratio;
		seekPos = nextPos + vSteering;

		glm::vec3 vFinal = seekPos - curPos;
		float vFinalMag = sqrtf(powf(vFinal.x, 2) + powf(vFinal.y, 2) + powf(vFinal.z, 2));
		if (vFinalMag > 0.005)
		{
			glm::vec3 vFinalI = vFinal / vFinalMag;
			m_vCurVelocity = vFinalI;
		}
	}
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek < 3.0f)
	{
		m_vCurVelocity = { 0.0f,0.0f,0.0f };
	}
	objPosition += m_vCurVelocity;

}

void CEnemy::AIFlee(glm::vec3 _pos)
{
	glm::vec3 curPos = this->objPosition;
	glm::vec3 fleepos = { -_pos.x, -_pos.y, -_pos.z };
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek > 190.0f)
	{
		m_vCurVelocity = { 0.0f,0.0f,0.0f };
		objPosition = m_vCurVelocity;
	}
	else
	{
		AISeek(fleepos);
	}
}

float CEnemy::FindMagnitude(glm::vec3 _v3)
{
	float vFinalMag = sqrtf(powf(_v3.x, 2) + powf(_v3.y, 2) + powf(_v3.z, 2));
	return vFinalMag;
}
