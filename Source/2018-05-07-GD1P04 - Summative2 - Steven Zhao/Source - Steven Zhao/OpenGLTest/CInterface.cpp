//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CInterface.cpp
// Description	:	main implementation for CInterface
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //
#include "CControls.h"
#include "CSceneManager.h"
#include "CLevel.h"
#include "TextLabel.h"
#include "CEnemy.h"
// This Includes //
#include "CInterface.h"


// Types //
using namespace std;
CInterface * CInterface::pInterface;

CInterface * CInterface::GetInstance()
{
	if (!pInterface) // If this does not exist
	{
		pInterface = new CInterface(); //Create an instance of interface
	}

	return pInterface;	//Returns the static instance
}

void CInterface::DestroyInstance()
{
	if (pInterface)//If the instance exists
	{
		delete pInterface;	//Delete instance
		pInterface = nullptr;//Set the pointer to nullptr
	}
}

void CInterface::update()
{
	// casts the current scene to the sp of level
	std::shared_ptr<CLevel>Level = std::dynamic_pointer_cast<CLevel>(CSceneManager::GetInstance()->GetCurrentScene());
	
	//When spacebar is pressed 
	if (CControls::GetInstance()->cKeyState[32] == CControls::INPUT_FIRST_PRESSED)//Set up first pressed 
	{
		if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::MENU)
		{
			CSceneManager::GetInstance()->switchScene(CSceneManager::LEVEL);
		}	
		else if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::END)
		{
			CInterface::GetInstance()->iScore = 0;
			CSceneManager::GetInstance()->switchScene(CSceneManager::MENU);
			label.SetPosition(glm::vec2(100.0f, 650.0f));
		}
	}
	
	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::END)
	{
		
		label.SetPosition(glm::vec2(Utility::SCR_WIDTH / 2.5, Utility::SCR_HEIGHT / 2));
		
	}

	if (Level)
	{

		label.SetText("Score: " + std::to_string(iScore));
		
	}

	//have another label for win conditon, 
}

void CInterface::render()
{
	label.Render();

	if (CSceneManager::GetInstance()->nCurrentScene == CSceneManager::END)
	{
		if (bWon)
		{
			WinText.Render();

		}
		else
		{
			LostText.Render();

		}
			
	}	
}

// Constructor //
CInterface::CInterface()
	:label("Score: ", "Resources/fonts/waltographUI.ttf", glm::vec2(100.0f, 650.0f)), WinText("You Won!", "Resources/fonts/waltographUI.ttf", glm::vec2(Utility::SCR_WIDTH/2.5 , (Utility::SCR_HEIGHT / 2) + 100.0f )), LostText("You Lost!", "Resources/fonts/waltographUI.ttf", glm::vec2(Utility::SCR_WIDTH / 2.5, (Utility::SCR_HEIGHT / 2) + 100.0f)), FPSCounter("FPS: ", "Resources/fonts/waltographUI.ttf", glm::vec2(Utility::SCR_WIDTH - 300.0f, 650.0f))
{
	WinText.SetScale(1.0f);
	FPSCounter.SetScale(1.0f);
	label.SetScale(1.0f);
	label.SetColor(glm::vec3(1.0f, 1.0f, 0.2f));
	WinText.SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	LostText.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	FPSCounter.SetColor(glm::vec3(1.0f, 0.5f, 0.0f));
}

// Destructor //
CInterface::~CInterface()
{

}

