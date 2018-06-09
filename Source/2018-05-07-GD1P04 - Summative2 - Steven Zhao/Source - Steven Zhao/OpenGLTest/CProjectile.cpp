#include "CProjectile.h"

CProjectile::CProjectile() { m_iAliveTime = 0; }
CProjectile::~CProjectile() {}

void CProjectile::update(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	m_iAliveTime++;
	CollisionCheck(_player, _CollisionObjects); 
	objPosition += m_CurrentVelo;
}

void CProjectile::CollisionCheck(CPlayer &_player, std::vector<std::shared_ptr<CSprite>>* _CollisionObjects)
{
	if (m_iProjectileType == CUtility::MY_PROJ)
	{
		if (!_CollisionObjects->empty())
		{
			for (auto it1 : *_CollisionObjects)
			{
				if (it1->iObjectMechanicsType == CUtility::ENEMY)
				{
					if (FindMagnitude(it1->objPosition - objPosition) < it1->fRadius + fRadius)
					{
						dynamic_pointer_cast<CEnemy>(it1)->m_iHealth -= 10;
						m_iAliveTime = 400;
						return;
					}
				}
			}
		}
	}

}