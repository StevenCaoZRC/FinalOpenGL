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
class CPlayer;
class CEnemy : public CSprite
{
    // Member Functions //
public:
	CEnemy();
	CEnemy(const char* _fileName, float fWidth, float fHeight, int iShape);
	~CEnemy();
	float fJumpHeight;
	float fMoveSpeed;
	void init(float _fMoveSpeed, float _fJumpHeight);

	//AI functions
	glm::vec3 AISeek(glm::vec3 _pos);
	glm::vec3 AIFlee(glm::vec3 _pos, float _seperatDistance);
	glm::vec3 AIChase(CPlayer &_player);
	glm::vec3 AIEvade(CPlayer &_player, float _seperatDistance);
	glm::vec3 AIArrivalSeek(glm::vec3 _pos, float _fArrivalRadius);
	glm::vec3 AIWander(int _iTimer);
	glm::vec3 AIObstacleAvoid(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	glm::vec3 AIFLocking(CPlayer &_player);
	glm::vec3 AIPathFollow(std::vector<glm::vec3>* _points, float _pathRadius);
	glm::vec3 AIseperation(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _seperatDistance);
	glm::vec3 AICohesion(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _cohesionDistance);
	glm::vec3 AIAlignment(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects, float _alignDistance);
	void Movement(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	void update(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	bool bIsAlive = true;
	bool bIsGoingRight = true;
	glm::vec3 new_movement;

	float m_fSteeringRatio = 9.0f;
	glm::vec3 m_vCurVelocity = { 0.0f,0.0f,0.0f };
	int m_iWanderTimer;
	float m_fWanderAngle;
	std::vector<glm::vec3> m_vPoints;
	int m_iPointsReached;
	float m_fSeeAheadDistance;
};

#endif // _CENEMY_H__

