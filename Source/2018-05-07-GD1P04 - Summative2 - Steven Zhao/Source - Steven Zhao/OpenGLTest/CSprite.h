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
#include "Model.h"
// Types //

// Constants //

// Prototypes //
class CEnemy;
class CSprite : public std::enable_shared_from_this<CSprite>//this allows me to return shared ptr form itself(using keyword THIS)
{
	// Member Functions //
public:
	enum Shapes {
		CUBE = 0,
		SPHERE,
	};

<<<<<<< HEAD
	CSprite();
=======
	//3D
	enum Shapes {
		CUBE = 0,
		SPHERE,
	};
	CSprite(const char* _fileName, float fWidth, float fHeight, int iShape);
>>>>>>> Michael-Test
	~CSprite();
	//3D
	void init3D(const char* _fileName, float fWidth, float fHeight, int iShape);
	virtual void render3D();
	//2D
	void init2D(const char* _fileName, float fWidth, float fHeight);
	virtual void render();
	void initModel(std::string path, GLuint program);
	virtual void renderModel();

	virtual void CSprite::update();

	void addFrame(const char* _filename);
	std::vector<GLuint> ImgArray;
	int nWidth;
	int nHeight;
	int m_iShape;

	GLuint vao;
	std::vector<GLuint> textures;
	GLuint tex;
<<<<<<< HEAD
	std::shared_ptr<Model> m_3DModel;
	int m_iObjType;

	int iCurrentFrame = 0;
	//Sphere stuff
	int DrawType;
	GLuint IndiceCount;
	//For MVP
=======
	//GLuint tex1;
	//GLuint tex2;

	int iCurrentFrame = 0;
	int DrawType;
	int iObjectType;
	void ScaleSprite(float _scale);
	GLuint IndiceCount;

>>>>>>> Michael-Test
	glm::vec3 objPosition = { 0.0f,0.0f,0.0f };
	glm::vec3 objRotate = {0.0f,0.0f,0.0f};
	glm::vec3 objScale = {1.0f,1.0f,1.0f};
	CEnemy* m_myEnemy;
	float fRadius;
};



