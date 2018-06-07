#include "CCollisionManager.h"

CCollisionManager::CCollisionManager(){}
CCollisionManager::~CCollisionManager(){}

void CCollisionManager::CollisionCheck(std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	if (!_CollisionObjects->empty())
	{
		for (auto it1 : *_CollisionObjects)
		{
			for (auto it2 : *_CollisionObjects)
			{
				if (it1->fRadius + it2->fRadius > DistanceBetween(it1.get(), it2.get()) && it1 != it2)
				{

				}
			}
		}

	}
}

float CCollisionManager::DistanceBetween(CSprite *_obj1, CSprite *_obj2)
{
	if (_obj1 != nullptr && _obj2 != nullptr)
	{
		glm::vec3 vDistance = _obj1->objPosition - _obj2->objPosition;
		float fDistance = sqrtf(powf(vDistance.x, 2) + powf(vDistance.y, 2) + powf(vDistance.z, 2));
		return fDistance;
	}
	return 0.0f;
}


