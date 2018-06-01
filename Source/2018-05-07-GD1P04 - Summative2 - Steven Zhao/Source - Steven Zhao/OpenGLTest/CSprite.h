 //
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CSprite.h
// Description	:	header file outlining the CSprite
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

// Library Includes //
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include <memory>
#include <vector>
// Local Includes //
#include "TextureLoader.h"
#include "ShaderLoader.h"
#include "Utils.h" 
#include "CCamera.h"
// Types //

// Constants //

// Prototypes //

class CSprite : public std::enable_shared_from_this<CSprite>//this allows me to return shared ptr form itself(using keyword THIS)
{
	// Member Functions //
public:
	//2D
	//CSprite(const char* _fileName, float fWidth, float fHeight);

	//3D
	CSprite(const char* _fileName, float fWidth, float fHeight);
	~CSprite();

	virtual void render();
	virtual void update();
	virtual void render3D();
	virtual void update3D();
	void addFrame(const char* _filename);
	std::vector<GLuint> ImgArray;
	int nWidth;
	int nHeight;

	GLuint vao;
	std::vector<GLuint> textures;
	//GLuint tex1;
	//GLuint tex2;

	int iCurrentFrame = 0;

	glm::vec3 objPosition = { 0.0f,0.0f,0.0f };
	glm::vec3 objRotate = {0.0f,0.0f,0.0f};
	glm::vec3 objScale = {1.0f,1.0f,1.0f};
};



