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
CEnemy::CEnemy()
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
	m_vCurVelocity = { 0.0f, 0.0f, 0.0f };
	m_iWanderTimer = 0;
	m_fWanderAngle = 0.0f;
	m_vPoints.push_back(glm::vec3(50.0f, 50.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(-50.0f, 50.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(-50.0f, -50.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(50.0f, -50.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	m_iPointsReached = 0;
}

void CEnemy::update(CPlayer &_player)
{
	if (bIsAlive)
	{

	}
	m_iWanderTimer++;
	if (m_iWanderTimer >= 1)
	{
		m_iWanderTimer = 0;
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
		vSteering = vSteering / m_fSteeringRatio;
		seekPos = nextPos + vSteering;

		glm::vec3 vFinal = seekPos - curPos;
		float vFinalMag = sqrtf(powf(vFinal.x, 2) + powf(vFinal.y, 2) + powf(vFinal.z, 2));
		if (vFinalMag > 0.005)
		{
			glm::vec3 vFinalI = vFinal / vFinalMag;
			m_vCurVelocity = vFinalI * fMoveSpeed;
		}
	}
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek < 2.0f)
	{
		m_vCurVelocity = { 0.0f,0.0f,0.0f };
	}
	if (FindMagnitude(m_vCurVelocity) > 0.001f)
	{
		objPosition += m_vCurVelocity;
	}
}

void CEnemy::AIFlee(glm::vec3 _pos)
{
	glm::vec3 curPos = this->objPosition;
	glm::vec3 fleepos;
	if (objPosition.x - _pos.x > 0)
	{
		fleepos.x = objPosition.x + 100.0f;
	}
	else
	{
		fleepos.x = objPosition.x - 100.0f;
	}
	if (objPosition.y - _pos.y > 0)
	{
		fleepos.y = objPosition.y + 100.0f;
	}
	else
	{
		fleepos.y = objPosition.y - 100.0f;
	}
	fleepos.z = objPosition.z;
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek > 50.0f)
	{
		m_vCurVelocity = { 0.0f,0.0f,0.0f };
	}
	else
	{
		AISeek(fleepos);
	}
}

void CEnemy::AIChase(CPlayer &_player)
{
	float fDistanceFromPLayer = FindMagnitude((_player.objPosition - this->objPosition));
	float fTImeForward = fDistanceFromPLayer / fMoveSpeed;
	glm::vec3 vVeloObj = glm::vec3(_player.v2_Movement, 0.0f);
	glm::vec3 vPosObj = _player.objPosition;
	glm::vec3 futureMovement = { vVeloObj.x * fTImeForward, vVeloObj.y * fTImeForward ,vVeloObj.z * fTImeForward };
	glm::vec3 seekPos = vPosObj + futureMovement;
	AISeek(seekPos);
}

void CEnemy::AIEvade(CPlayer & _player)
{
	float fDistanceFromPLayer = FindMagnitude((_player.objPosition - this->objPosition));
	float fTImeForward = fDistanceFromPLayer / fMoveSpeed;
	if (fDistanceFromPLayer < _player.fMovementSpeed * 60.0f)
	{
		glm::vec3 vVeloObj = glm::vec3(_player.v2_Movement, 0.0f);
		glm::vec3 vPosObj = _player.objPosition;
		glm::vec3 futureMovement = { vVeloObj.x * fTImeForward, vVeloObj.y * fTImeForward ,vVeloObj.z * fTImeForward };
		glm::vec3 seekPos = vPosObj + futureMovement;
		AIFlee(seekPos);
	}
}

void CEnemy::AIArrivalSeek(glm::vec3 _pos, float _fArrivalRadius)
{
	//current pos = current position of this item
	glm::vec3 curPos = this->objPosition;
	glm::vec3 seekPos;
	glm::vec3 nextPosSeek;
	glm::vec3 nextPos = objPosition + m_vCurVelocity;
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
		vSteering = vSteering / m_fSteeringRatio;
		seekPos = nextPos + vSteering;

		glm::vec3 vFinal = seekPos - curPos;
		float vFinalMag = sqrtf(powf(vFinal.x, 2) + powf(vFinal.y, 2) + powf(vFinal.z, 2));
		if (vFinalMag > 0.005)
		{
			glm::vec3 vFinalI = vFinal / vFinalMag;
			m_vCurVelocity = vFinalI * fMoveSpeed;
		}
	}
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek < 2.0f)
	{
		m_vCurVelocity = { 0.0f,0.0f,0.0f };
	}
	else if (DistanceSeek < _fArrivalRadius && objPosition != _pos)
	{
		float fDecelerateRate;
		fDecelerateRate = DistanceSeek / 15.0f;
		m_vCurVelocity = fDecelerateRate * (m_vCurVelocity / FindMagnitude(m_vCurVelocity));
	}
	if (FindMagnitude(m_vCurVelocity) > 0.001f)
	{
		objPosition += glm::vec3(m_vCurVelocity.x, m_vCurVelocity.y, 0.0f);
	}
}

void CEnemy::AIWander(int _iTimer)
{
	if (_iTimer == 0)
	{
		float fPI = 3.1415926f;
		int iRandDeg = rand() % 3 - 2;
		float fRandRadi = (float)iRandDeg * fPI / 180.0f;
		m_fWanderAngle += fRandRadi;
		glm::vec3 WanderCenter;
		glm::vec3 distance = (fMoveSpeed * 30.0f) * m_vCurVelocity;
		WanderCenter = (objPosition + distance); //glm::vec3(m_vCurVelocity.x * 1000000000000000.0f, m_vCurVelocity.y * 10000000000000000.0f, 0.0f);
		glm::vec3 WanderPos;
		WanderPos = glm::vec3(WanderCenter.x, WanderCenter.y + 10.0f, 0.0f);
		float fWanderPosOldX = WanderPos.x;
		float fWanderPosOldY = WanderPos.y;
		WanderPos.x = fWanderPosOldX * cos(m_fWanderAngle) - fWanderPosOldY * sin(m_fWanderAngle);
		WanderPos.y = fWanderPosOldY * cos(m_fWanderAngle) + fWanderPosOldX * sin(m_fWanderAngle);
		AISeek(WanderPos);
		/*glm::vec3 WanderForce = WanderPos - objPosition;
		if (FindMagnitude(WanderForce) > 0.005f)
		{
		WanderForce = WanderForce / FindMagnitude(WanderForce);
		WanderForce = fMoveSpeed * WanderForce;
		WanderForce = WanderForce / m_fSteeringRatio;
		}
		m_vCurVelocity += WanderForce;
		if (FindMagnitude(m_vCurVelocity) > 0.005f)
		{
		m_vCurVelocity = m_vCurVelocity / FindMagnitude(m_vCurVelocity);
		m_vCurVelocity = (fMoveSpeed * 0.5f) * m_vCurVelocity;
		}*/
	}
	//objPosition += m_vCurVelocity;
}

void CEnemy::AIObstacleAvoid()
{

}

void CEnemy::AIFLocking(CPlayer & _player)
{

}

void CEnemy::AIPathFollow(std::vector<glm::vec3>* _points)
{
	if ((unsigned)m_iPointsReached < _points->size())
	{
		AISeek(_points->at(m_iPointsReached));
	}
	if ((unsigned)m_iPointsReached < _points->size())
	{
		if (FindMagnitude((objPosition - _points->at(m_iPointsReached))) < 5.0f)
		{
			m_iPointsReached++;
		}
	}
	if ((unsigned)m_iPointsReached >= _points->size())
	{
		m_iPointsReached = 0;
	}
}


float CEnemy::FindMagnitude(glm::vec3 _v3)
{
	float vFinalMag = sqrtf(powf(_v3.x, 2) + powf(_v3.y, 2) + powf(_v3.z, 2));
	return vFinalMag;
}