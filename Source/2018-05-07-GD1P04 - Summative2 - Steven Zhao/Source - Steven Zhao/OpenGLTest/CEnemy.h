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
	~CEnemy();
	float fJumpHeight;
	float fMoveSpeed;
	void init(float _fMoveSpeed, float _fJumpHeight);
<<<<<<< HEAD
	void update(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	glm::vec3 AISeek(glm::vec3 _pos);
	glm::vec3 AIFlee(glm::vec3 _pos);
	glm::vec3 AIChase(CPlayer &_player);
	glm::vec3 AIEvade(CPlayer &_player);
	glm::vec3 AIArrivalSeek(glm::vec3 _pos, float _fArrivalRadius);
	glm::vec3 AIWander(int _iTimer);
	glm::vec3 AIObstacleAvoid(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	glm::vec3 AIFLocking(CPlayer &_player);
	glm::vec3 AIPathFollow(std::vector<glm::vec3>* _points);
	void Movement(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
=======
	void update(CPlayer &_player);

	//AI functions
	void AISeek(glm::vec3 _pos);
	void AIFlee(glm::vec3 _pos);
	void AIChase(CPlayer &_player);
	void AIEvade(CPlayer &_player);
	void AIArrivalSeek(glm::vec3 _pos, float _fArrivalRadius);
	void AIWander(int _iTimer);
	void AIObstacleAvoid();
	void AIFLocking(CPlayer &_player);
	void AIPathFollow(std::vector<glm::vec3>* _points);
>>>>>>> master
	bool bIsAlive = true;
	bool bIsGoingRight = true;
	float FindMagnitude(glm::vec3 _v3);

private:
	float m_fSteeringRatio = 20.0f;
	glm::vec3 m_vCurVelocity = { 0.0f,0.0f,0.0f };
	int m_iWanderTimer;
	float m_fWanderAngle;
	std::vector<glm::vec3> m_vPoints;
	int m_iPointsReached;
	float m_fSeeAheadDistance;
};

#endif // _CENEMY_H__

