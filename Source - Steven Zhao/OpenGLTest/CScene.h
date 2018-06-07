//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CScene.h
// Description	:	header file outlining the CScene
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

// Library Includes //
#include <vector>
#include <memory>
// Local Includes //
#include "CSprite.h"
//class CSprite; 
class CScene 
{
public:
    CScene();
    ~CScene();
	virtual void render();
	virtual void update();
	void DeleteSprite(std::shared_ptr<CSprite> TobeDeleted);
	void SpritesAdd(std::shared_ptr<CSprite> AddSpr);
	//vector of entites taht getscalled in render
	std::vector<std::shared_ptr<CSprite>> v_SpritesInScene;
};



