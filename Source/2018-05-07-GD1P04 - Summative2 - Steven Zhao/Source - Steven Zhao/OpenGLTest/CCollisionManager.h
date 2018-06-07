#ifndef _CCOLLISIONMANAGER_H__
#define _CCOLLISIONMANAGER_H__
// Library Includes //
#include <memory>
#include <vector>
// Local Includes //
#include "CScene.h"
#include"TextLabel.h"

// Types //

// Constants //

// Prototypes //
class CEnemy;
class CPlayer;
class CSprite;
class CCubeMap;

class CCollisionManager
{
	CCollisionManager();
	~CCollisionManager();

	void CollisionCheck(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects);
	float DistanceBetween(CSprite* _obj1, CSprite* _obj2);
};


#endif