//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	Utils.h
// Description	:	header file outlining the Utilities
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once
// Local Includes //
#include "ShaderLoader.h"
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include "TextureLoader.h"

// Prototype //
class CUtility
{
public:
	CUtility();
	~CUtility();
	
	struct position
	{
		float fX, fY, fZ;
	};
	struct texCoord
	{
		float fX, fY;
	};
	struct vertexFMT
	{
		float fX, fY, fZ;
		float fNX, fNY, fNZ;
		float fS0, fT0;
	};
	struct colour
	{
		float fR;
		float fG;
		float fB;
		float fA;
	};
	
	static GLuint program;
	static GLuint CubemapProgram;
	enum SpriteType
	{
		ENEMY = 0,
		PLAYER,
		IMOBIL_WALL,
		MOBIL_WALL,
		NON_SOLID,
	};
	

private: 
	float fWidth;
	float fHeight;
	
};

namespace Utility
{
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 750;

}


