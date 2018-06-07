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
	CCubeMap(std::vector<std::string> _filePaths);
	~CCubeMap();
	void render();
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint tex;
	GLuint cubemapProgram;
	glm::vec3 objPosition = { 0.0f,0.0f,0.0f };
	glm::vec3 objRotate = { 0.0f,0.0f,0.0f };
	glm::vec3 objScale = { 1.0f,1.0f,1.0f };

};

#pragma once
