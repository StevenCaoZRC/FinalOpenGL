//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CSceneManager.h
// Description	:	header file outlining the CSceneManager
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CSCENEMANAGER_H__
#define _CSCENEMANAGER_H__

// Library Includes //
#include <vector>
#include <time.h>
#include <memory>
// Local Includes //
#include "CCamera.h"
#include "CSprite.h"
#include "Utils.h"
#include "CScene.h"
#include "CControls.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CLevel.h"
// Types //

// Constants //

// Prototypes //

class CSceneManager
{
	// Member Functions //
public:
	enum DiffScenes
	{
		MENU, //0
		LEVEL,//1
		END,  //2
	};
	static CSceneManager* GetInstance(); 
	static void DestroyInstance();
	void RenderCurrent();
	void UpdateCurrent(); 
	void init();
	void switchScene(int nNewScene);
	void SceneAdd(std::shared_ptr<CScene>AddSc); //Adds current scene to vector
	std::shared_ptr<CScene> GetCurrentScene() { return Scenes[nCurrentScene]; }; //Gets the current scene from the scene vector
	std::vector < std::shared_ptr<CScene> >Scenes;
	int nCurrentScene = 0;
	
private:
	CSceneManager();
	~CSceneManager();
	static CSceneManager* pSceneManager;
	CSceneManager(CSceneManager const&) = delete; //Deletes copy constructor
	void operator = (CSceneManager const&) = delete; //Deletes the operator assigned to the copy constructor

};

#endif // _CSCENEMANAGER_H__

