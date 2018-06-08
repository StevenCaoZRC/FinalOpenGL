//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CLevel.h
// Description	:	header file outlining the CLevel
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CLEVEL_H__
#define _CLEVEL_H__

// Library Includes //
#include <memory>
#include <vector>
// Local Includes //
#include "CScene.h"
#include"TextLabel.h"
#include "Model.h"

// Types //

// Constants //

// Prototypes //
class CEnemy;
class CPlayer;
class CSprite;
class TextLabel;
class CCubeMap;

class CLevel : public CScene
{
    // Member Functions //
        public:
            CLevel();
            ~CLevel();
			void addPlayer();
			void addEnemy();
			void addLevel();
			void addMenu();
			void addCubeMap();
			void addModels();
			void addEndMenu();
			void render();
			void update();
			void resetLevel();
			void delEnemy(std::shared_ptr<CEnemy>);
			std::vector<std::shared_ptr<CEnemy>> v_Enemies;
			std::shared_ptr<CPlayer>CharacterSpr;
			std::shared_ptr<CSprite>EndSpr;
			std::vector<std::shared_ptr<CSprite>> v_CollisionObjects;
			int nScore = 0;
			glm::vec3 MousePointPos;
        private:
			std::shared_ptr<Model> Tank;
			CCubeMap * m_cubemap;
			glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
};

#endif // _CLEVEL_H__

