//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CScene.cpp
// Description	:	main implementation for CScene
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
// Local Includes //
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Utils.h" 
#include "CCamera.h"
#include "Sphere.h"
// This Includes //
#include "CScene.h"

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;

// Constructor //
CScene::CScene()
{

}

// Destructor //
CScene::~CScene()
{
	v_SpritesInScene.clear();
}

void CScene::render()
{
	for (auto it : v_SpritesInScene)
	{
		////2D
		//it->render();

		//3D
		it->render3D();

	}
}

void CScene::update()
{
	for (auto it : v_SpritesInScene)
	{
		it->update();
	}
}

void CScene::DeleteSprite(std::shared_ptr<CSprite> TobeDeleted)
{
	for (auto it = v_SpritesInScene.begin(); it != v_SpritesInScene.end(); it++)
	{
		if ((*it) == TobeDeleted)
		{
			v_SpritesInScene.erase(it);
			break;
		}
		
	}
}

void CScene::SpritesAdd(std::shared_ptr<CSprite> AddSpr)
{
	v_SpritesInScene.push_back(AddSpr);
}

