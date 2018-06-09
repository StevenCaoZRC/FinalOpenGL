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
#include "CProjectile.h"
// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;

// Constructor //
CEnemy::CEnemy() {}
CEnemy::CEnemy(const char * _fileName, float fWidth, float fHeight, int iShape) : CSprite()
{
}

// Destructor //
CEnemy::~CEnemy()
{

}

void CEnemy::init(float _fMoveSpeed, float _fJumpHeight, int _hp)
{
	m_iHealth = _hp;
	fMoveSpeed = _fMoveSpeed;
	fJumpHeight = _fJumpHeight;
	m_vCurVelocity = { 0.0f, 0.0f, 0.0f };
	m_iWanderTimer = 0;
	m_fWanderAngle = 0.0f;
	m_vPoints.push_back(glm::vec3(450.0f, 200.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(-450.0f, 200.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(-450.0f, -200.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(450.0f, -200.0f, 0.0f));
	m_vPoints.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	m_iPointsReached = 0;
}


void CEnemy::update(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	if (bIsAlive)
	{
		Movement(_player, _CollisionObjects);
		MeleeCollisionCheck(_player);
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


glm::vec3 CEnemy::AISeek(glm::vec3 _pos)
{
	//current pos = current position of this item
	glm::vec3 curPos = objPosition;
	glm::vec3 seekPos;
	glm::vec3 nextPosSeek;
	glm::vec3 vFinal;
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

		vFinal = seekPos - curPos;
		float vFinalMag = sqrtf(powf(vFinal.x, 2) + powf(vFinal.y, 2) + powf(vFinal.z, 2));
		if (vFinalMag > 0.005)
		{
			float DistanceSeek = FindMagnitude((_pos - curPos));
			if (DistanceSeek < 2.0f)
			{
				return glm::vec3(0.0f, 0.0f, 0.0f);
			}
			else
			{
				glm::vec3 vFinalI = vFinal / vFinalMag;
				return vFinal;
			}
		}
		else
		{
			return glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}
	return vFinal;
}
glm::vec3 CEnemy::AIFlee(glm::vec3 _pos, float _seperatDistance)
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
	if (DistanceSeek > _seperatDistance)
	{
		return (glm::vec3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		return (AISeek(fleepos));
	}
}

glm::vec3 CEnemy::AIChase(CPlayer &_player)
{
	float fDistanceFromPLayer = FindMagnitude((_player.objPosition - this->objPosition));
	float fTImeForward = fDistanceFromPLayer / fMoveSpeed;
	glm::vec3 vVeloObj = glm::vec3(_player.v2_Movement, 0.0f);
	glm::vec3 vPosObj = _player.objPosition;
	glm::vec3 futureMovement = { vVeloObj.x * fTImeForward, vVeloObj.y * fTImeForward ,vVeloObj.z * fTImeForward };
	glm::vec3 seekPos = vPosObj + futureMovement;
	return (AISeek(seekPos));
}

glm::vec3 CEnemy::AIEvade(CPlayer & _player, float _seperatDistance)
{
	float fDistanceFromPLayer = FindMagnitude((_player.objPosition - this->objPosition));
	float fTImeForward = fDistanceFromPLayer / fMoveSpeed;
	if (fDistanceFromPLayer < _player.fMovementSpeed * 60.0f)
	{
		glm::vec3 vVeloObj = glm::vec3(_player.v2_Movement, 0.0f);
		glm::vec3 vPosObj = _player.objPosition;
		glm::vec3 futureMovement = { vVeloObj.x * fTImeForward, vVeloObj.y * fTImeForward ,vVeloObj.z * fTImeForward };
		glm::vec3 seekPos = vPosObj + futureMovement;
		return (AIFlee(seekPos, _seperatDistance));
	}
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 CEnemy::AIArrivalSeek(glm::vec3 _pos, float _fArrivalRadius)
{
	//current pos = current position of this item
	glm::vec3 curPos = this->objPosition;
	glm::vec3 seekPos;
	glm::vec3 nextPosSeek;
	glm::vec3 nextPos = objPosition + m_vCurVelocity;
	glm::vec3 vFinal;
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

		vFinal = seekPos - curPos;
		float vFinalMag = sqrtf(powf(vFinal.x, 2) + powf(vFinal.y, 2) + powf(vFinal.z, 2));
		if (vFinalMag > 0.005)
		{
			glm::vec3 vFinalI = vFinal / vFinalMag;
			vFinal = vFinalI * fMoveSpeed;
		}
	}
	float DistanceSeek = FindMagnitude((_pos - curPos));
	if (DistanceSeek < 2.0f)
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else if (DistanceSeek < _fArrivalRadius && objPosition != _pos)
	{
		float fDecelerateRate;
		fDecelerateRate = (DistanceSeek) / _fArrivalRadius;
		return (fDecelerateRate * vFinal);
	}
	else
	{
		return vFinal;
	}
}

glm::vec3 CEnemy::AIWander(int _iTimer)
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
	return { 0.0f,0.0f,0.0f };
}

glm::vec3 CEnemy::AIObstacleAvoid(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	glm::vec3 SeeAhead;
	if (FindMagnitude(m_vCurVelocity) > 0.0005f)
	{
		SeeAhead = objPosition + (m_vCurVelocity / FindMagnitude(m_vCurVelocity)) * fMoveSpeed * 10.0f;
	}
	else
	{
		SeeAhead = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 SeeAheadHalf = SeeAhead * fMoveSpeed;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	CSprite *ClosestCollision = nullptr;
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::IMOBIL_WALL)
			{
				if (FindMagnitude(SeeAhead - it1->objPosition) <= it1->fRadius
					|| FindMagnitude(SeeAheadHalf - it1->objPosition) <= it1->fRadius
					|| FindMagnitude(objPosition - it1->objPosition) <= it1->fRadius
					&& this != it1.get())
				{
					if (ClosestCollision != nullptr
						&& FindMagnitude(objPosition - ClosestCollision->objPosition) > FindMagnitude(objPosition - it1->objPosition))
					{
						AvoidanceVector = SeeAhead - it1->objPosition;
						if (FindMagnitude(AvoidanceVector) > 0.0005f)
						{
							AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
						}
					}
					else
					{
						ClosestCollision = it1.get();
						AvoidanceVector = SeeAhead - it1->objPosition;
						if (FindMagnitude(AvoidanceVector) > 0.0005f)
						{
							AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
						}
					}
				}
			}
		}
	}
	return (AvoidanceVector);

}

glm::vec3 CEnemy::AIFLocking(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, CPlayer & _player)
{
	glm::vec3 flocking;
	flocking += AIseperation(_CollisionObjects, 1.0f);
	flocking += AICohesion(_CollisionObjects, 50.0f);
	flocking += AIAlignment(_CollisionObjects, 50.0f);
	return flocking;
}

glm::vec3 CEnemy::AIPathFollow(std::vector<glm::vec3>* _points, float _pathRadius)
{
	glm::vec3 temp = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 CurrentLine = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LineToObjectFromPreviousPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	float DotProduct = 0.0f;
	if (m_iPointsReached == 0)
	{
		CurrentLine = _points->back() - _points->at(0);
		LineToObjectFromPreviousPoint = objPosition + new_movement - _points->at(m_iPointsReached);
	}
	else
	{
		CurrentLine = _points->at(m_iPointsReached - 1) - _points->at(m_iPointsReached);
		LineToObjectFromPreviousPoint = objPosition + new_movement - _points->at(m_iPointsReached);
	}
	float theta = (CurrentLine.x * LineToObjectFromPreviousPoint.x + CurrentLine.y * LineToObjectFromPreviousPoint.y) 
		/ (FindMagnitude(CurrentLine) * FindMagnitude(LineToObjectFromPreviousPoint));
	theta = acosf(theta);
	glm::vec3 CurrentLineI = CurrentLine / FindMagnitude(CurrentLine);
	float Multiplier = (FindMagnitude(LineToObjectFromPreviousPoint) * cosf(theta));
	glm::vec3 TargetPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	TargetPoint = _points->at(m_iPointsReached) + CurrentLineI * Multiplier;
	float Distance2Path = FindMagnitude(objPosition - TargetPoint);

	if (Distance2Path > _pathRadius)
	{
		temp = AISeek(TargetPoint);
	}
	else
	{
		temp = AISeek(_points->at(m_iPointsReached));
	}

	if ((unsigned)m_iPointsReached < _points->size())
	{
		if (FindMagnitude((objPosition - _points->at(m_iPointsReached))) < _pathRadius)
		{
			m_iPointsReached++;
		}
	}
	if ((unsigned)m_iPointsReached >= _points->size())
	{
		m_iPointsReached = 0;
	}

	return temp;
}

glm::vec3 CEnemy::AIseperation(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _seperatDistance)
{
	float iTotalNeedingSeperation = 0.0f;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::ENEMY)
			{
				if (FindMagnitude(objPosition - it1->objPosition) <= this->fRadius + it1->fRadius  + _seperatDistance //+ _seperatDistance
					&& this != it1.get())
				{
					if (FindMagnitude(objPosition - it1->objPosition) > 0.0005f)
					{
						glm::vec3 temp = objPosition - it1->objPosition;
						AvoidanceVector += temp;
						iTotalNeedingSeperation += 1.0f;
					}
				}
			}
		}
	}
	if (FindMagnitude(AvoidanceVector) > 0.0005f)
	{
		AvoidanceVector = AvoidanceVector / iTotalNeedingSeperation;
		AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
	}
	else
	{
		AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return AvoidanceVector;
}

glm::vec3 CEnemy::AICohesion(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _cohesionDistance)
{
	float iTotalNeedingSeperation = 0.0f;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::ENEMY)
			{
				if (FindMagnitude(objPosition - it1->objPosition) <= _cohesionDistance
					&& this != it1.get())
				{
					if (FindMagnitude(objPosition - it1->objPosition) > 0.0005f)
					{
						glm::vec3 temp = it1->objPosition - objPosition;
						AvoidanceVector += temp;
						iTotalNeedingSeperation += 1.0f;
					}
				}
			}
		}
	}
	if (FindMagnitude(AvoidanceVector) > 0.0005f)
	{
		AvoidanceVector = AvoidanceVector / iTotalNeedingSeperation;
		AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
	}
	else
	{
		AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return AvoidanceVector;
}

glm::vec3 CEnemy::AIAlignment(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _alignDistance)
{
	float iTotalNeedingSeperation = 0.0f;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::ENEMY || it1->iObjectMechanicsType == CUtility::PLAYER)
			{
				if (FindMagnitude(objPosition - it1->objPosition) <= _alignDistance
					&& this != it1.get())
				{
					if (FindMagnitude(objPosition - it1->objPosition) > 0.0005f)
					{
						shared_ptr<CEnemy> myEnemy;
						glm::vec3 temp;
						if (it1->iObjectMechanicsType == CUtility::ENEMY)
						{
							temp = dynamic_pointer_cast<CEnemy>(it1)->new_movement;
						}
						else
						{
							temp = dynamic_pointer_cast<CPlayer>(it1)->new_movement;
						}
						AvoidanceVector += temp;
						iTotalNeedingSeperation += 1.0f;
					}
				}
			}
		}
	}
	if (FindMagnitude(AvoidanceVector) > 0.0005f)
	{
		AvoidanceVector = AvoidanceVector / iTotalNeedingSeperation;
		AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
	}
	else
	{
		AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return AvoidanceVector;
}

glm::vec3 CEnemy::AIAvoidBullets(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _seperatDistance)
{
	float iTotalNeedingSeperation = 0.0f;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::MY_PROJ)
			{
				if (FindMagnitude(objPosition - it1->objPosition) <= this->fRadius + it1->fRadius + _seperatDistance //+ _seperatDistance
					&& this != it1.get())
				{
					if (FindMagnitude(objPosition - it1->objPosition) > 0.0005f)
					{
						glm::vec3 temp = objPosition - it1->objPosition;
						AvoidanceVector += temp;
						iTotalNeedingSeperation += 1.0f;
					}
				}
			}
		}
	}
	if (FindMagnitude(AvoidanceVector) > 0.0005f)
	{
		AvoidanceVector = AvoidanceVector / iTotalNeedingSeperation;
		AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
	}
	else
	{
		AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return AvoidanceVector;
}

glm::vec3 CEnemy::AIDodgeBullets(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _seperatDistance)
{
	float iTotalNeedingSeperation = 0.0f;
	glm::vec3 AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			if (it1->iObjectMechanicsType == CUtility::MY_PROJ)
			{
				if (FindMagnitude(objPosition - it1->objPosition) <= this->fRadius + it1->fRadius + _seperatDistance //+ _seperatDistance
					&& this != it1.get())
				{
					glm::vec3 temp;
					float fTImeForward = FindMagnitude(objPosition - it1->objPosition) / fMoveSpeed;
					glm::vec3 vVeloObj = dynamic_pointer_cast<CProjectile>(it1)->m_CurrentVelo;
					glm::vec3 vPosObj = it1->objPosition;
					glm::vec3 futureMovement = { vVeloObj.x * fTImeForward, vVeloObj.y * fTImeForward ,vVeloObj.z * fTImeForward };
					glm::vec3 seekPos = vPosObj + futureMovement;
					AvoidanceVector += AIFlee(seekPos, _seperatDistance);
					iTotalNeedingSeperation += 1.0f;
				}
			}
		}
	}
	if (FindMagnitude(AvoidanceVector) > 0.0005f)
	{
		AvoidanceVector = AvoidanceVector / iTotalNeedingSeperation;
		AvoidanceVector = AvoidanceVector / FindMagnitude(AvoidanceVector) * fMoveSpeed * 0.3f;
	}
	else
	{
		AvoidanceVector = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return AvoidanceVector;
}

void CEnemy::Movement(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	//m_vCurVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	new_movement += AISeek(_player.objPosition);
	new_movement += AIObstacleAvoid(_CollisionObjects) * 50.0f;
	new_movement += AIseperation(_CollisionObjects, 1.0f) * 5.0f;
	new_movement += AIDodgeBullets(_CollisionObjects, 30.0f) * 100.0f;
	//new_movement += AICohesion(_CollisionObjects, 50.0f) * 0.5f;
	//new_movement += AIAlignment(_CollisionObjects, 50.0f);
	//new_movement += AIPathFollow(&m_vPoints, 30.0f) * 10.0f;
	if (FindMagnitude(new_movement) > 0.0005f)
	{
		new_movement = new_movement / FindMagnitude(new_movement) * fMoveSpeed;
	}
	else
	{
		new_movement = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	if (FindMagnitude(new_movement) >= 0.005f)
	{
		m_vCurVelocity = new_movement;
	}
	objPosition += m_vCurVelocity;
}


void CEnemy::MeleeCollisionCheck(CPlayer &_player)
{
	if (FindMagnitude(_player.objPosition - objPosition) < _player.fRadius + fRadius)
	{
		m_iHealth = 0;
		_player.m_iHealth -= 5;
		bIsAlive = false;
		return;
	}
}
