//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CSceneManager.cpp
// Description	:	main implementation for CSceneManager
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz, michael.xu7480@mediadesign.school.nz
//

// Library Includes //
#include <time.h>
// Local Includes //
#include "CSound.h"
#include "CInterface.h"
#include "Sphere.h"
// This Includes //
#include "CSceneManager.h"

// Types //
using namespace std;
CSceneManager* CSceneManager::pSceneManager; // Redefining the static variable for class

/****************
* GetInstance: creates a single instance of scenemanager 
* @author(s): Steven, Michael
* @parameter: N/A
* @return: pointer to Scenemanager instance
*****************/
CSceneManager * CSceneManager::GetInstance()
{
	if (!pSceneManager) // If this does not exist
	{
		pSceneManager = new CSceneManager(); //Create an instance of SceneManager
	}

	return pSceneManager;	//Returns the static instance
}

/****************
* DestroyInstance: checks if the pointer exists, if so delete the pointer and set it to nullptr
* @author(s): Steven, Michael
* @parameter: N/A
* @return: N/A
*****************/
void CSceneManager::DestroyInstance()
{
	if (pSceneManager) //If the instance exists
	{
		delete pSceneManager;	//Delete instance
		pSceneManager = nullptr;//Set the pointer to nullptr
	}

}

/****************
* RenderCurrent: Renders the current scene selected along with the user interface.
* @author(s): Steven, Michael
* @parameter: N/A
* @return: N/A
*****************/
void CSceneManager::RenderCurrent()
{
	//Renders the current scene, as scenemanager manages multiple scenes.
	Scenes[nCurrentScene]->render(); //Rending the current scene 
	//renders text UI
	CInterface::GetInstance()->render();
	CInterface::GetInstance()->FPSCounter.Render();

}

void CSceneManager::UpdateCurrent()
{
	//Loads multiple Scenes
	Scenes[nCurrentScene]->update();
	
}

/****************
* Update:
* @author(s): Steven, Michael
* @parameter:
* @return:
*****************/
void CSceneManager::init()
{
	glutIgnoreKeyRepeat(1);
	ShaderLoader shaderloader;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	CUtility::program = shaderloader.CreateProgram("VertexShader.txt", "FragmentShader.txt");
	CUtility::modelProgram = shaderloader.CreateProgram("ModelVertShader.txt", "ModelFragShader.txt");
	CUtility::CubemapProgram = shaderloader.CreateProgram("CubeMapVer.txt", "CubeMapFrag.txt");
	


	//---------------|Level Scenes Stuff|---------------//
	//Gets the initial values of the controls
	CControls::GetInstance()->init();
	
	//creaing a shared pointer to level and bgSprite and CharacterSpr
	std::shared_ptr<CLevel>Level = make_shared<CLevel>();

	//Adding the level to scenemanager
	Level->addLevel();
	Level->addCubeMap();
	Level->addModels();
	Level->addEnemy();
	Level->addPlayer();
	
	//---------------|Menu Scenes Stuff|---------------//
	std::shared_ptr<CLevel> Menu = make_shared<CLevel>();
	Menu->addMenu();
	//Menu->addModels();
	//Menu->addCubeMap();
	//Do if clicked
	//std::shared_ptr<CSprite> startBtn1 = make_shared<CSprite>("Resources/start1.png", 0.0, 0.0);

	//---------------|End Scenes Stuff|---------------//
	std::shared_ptr<CLevel> End = make_shared<CLevel>();
	

	End->addEndMenu();
	//Adding the different scenes into a vector of scenes
	CSceneManager::GetInstance()->SceneAdd(Menu);
	CSceneManager::GetInstance()->SceneAdd(Level);
	CSceneManager::GetInstance()->SceneAdd(End);
}

void CSceneManager::switchScene(int nNewScene)
{
	//switches to the scene passed in the paramters, the different scenes are enums
	nCurrentScene = nNewScene;
}

void CSceneManager::SceneAdd(std::shared_ptr<CScene> AddSc)
{
	Scenes.push_back(AddSc);
}

// Constructor //
CSceneManager::CSceneManager()
{

}

// Destructor //
CSceneManager::~CSceneManager()
{
	Scenes.clear(); //Clears the vector
}

