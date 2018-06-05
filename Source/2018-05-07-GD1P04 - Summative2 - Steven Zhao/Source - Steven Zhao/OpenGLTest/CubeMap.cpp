//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CSprite.cpp
// Description	:	main implementation for CSprite
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// This Includes //
#include "CubeMap.h"

CCubeMap::CCubeMap(const char * _fileName)
{

	GLfloat cubeVertices[] = {
	// Positions    
	// Front Face
	-1.0f,  1.0f,  1.0f,  // 0
	 1.0f,  1.0f,  1.0f,  // 1
	 1.0f, -1.0f,  1.0f,  // 2
	-1.0f, -1.0f,  1.0f,  // 3

	// Right Face
	1.0f,  1.0f,  1.0f,   // 4
	1.0f,  1.0f, -1.0f,   // 5
	1.0f, -1.0f, -1.0f,   // 6
	1.0f, -1.0f,  1.0f,   // 7

	// Back Face
	 1.0f,  1.0f, -1.0f, // 8
	-1.0f,  1.0f, -1.0f, // 9
	-1.0f, -1.0f, -1.0f, // 10
	 1.0f, -1.0f, -1.0f, // 11

	// Left Face
	-1.0f,  1.0f, -1.0f, // 12
	-1.0f,  1.0f,  1.0f, // 13
	-1.0f, -1.0f,  1.0f, // 14
	-1.0f, -1.0f, -1.0f, // 15

	// Top Face
	-1.0f,  1.0f, -1.0f, // 16
	 1.0f,  1.0f, -1.0f, // 17
	 1.0f,  1.0f,  1.0f, // 18
	-1.0f,  1.0f,  1.0f, // 19

	// Bottom Face
	-1.0f, -1.0f,  1.0f, // 20
	 1.0f, -1.0f,  1.0f, // 21
	 1.0f, -1.0f, -1.0f, // 22
	-1.0f, -1.0f, -1.0f, // 23
	};

}

CCubeMap::~CCubeMap()
{
}
