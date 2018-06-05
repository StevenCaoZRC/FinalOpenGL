//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CEnemy.cpp
// Description	:	header file outlining the CCubeMap
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //
#include "CCamera.h"
#include "CSprite.h"
#include <vector>
class CCubeMap
{
public:
	CCubeMap(const char* _fileName);
	~CCubeMap();
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::vector<std::shared_ptr<CSprite>> v_CubeFace;

};

#pragma once
