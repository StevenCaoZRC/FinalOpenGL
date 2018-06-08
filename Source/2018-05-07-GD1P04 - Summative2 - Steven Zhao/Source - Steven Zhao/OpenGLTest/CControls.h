//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CControls.h
// Description	:	main implementation for CSprite
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//
#pragma once
//Library Includes
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "glew.h"
#include "freeglut.h"
//Global Variable

class CControls
{
public:
	enum KeyState
	{
		INPUT_FIRST_RELEASE = 0,	//First frame of Up state
		INPUT_RELEASED,			//Default State (Up)
		INPUT_FIRST_PRESSED,    //First frame of Down state
		INPUT_HOLD,				//Key is helded down
	};
	enum Mouse
	{
		MOUSE_LEFT = 0,			//0
		MOUSE_MIDDLE,		//1
		MOUSE_RIGHT,		//2
	};
	static CControls* GetInstance();
	static void DestroyInstance();

	unsigned char cKeyState[255];
	unsigned char cMouse[3];	
	void init();
	void update();
	static void InitKeyDown(unsigned char cKey, int nX, int nY);
	static void InitKeyUp(unsigned char cKey, int nX, int nY);
	void KeyDown(unsigned char cKey, int nX, int nY);
	void KeyUp(unsigned char cKey, int nX, int nY);
	static void MousePosPassive(int x, int y);
	void MousePosUpdate(int x, int y);
	

	void Mouse(int nButton, int nGlutState, int nX, int nY);


	float mouseX;
	float mouseY;
	float mouseZ;
	glm::vec3 ray_nds;
	glm::vec4 ray_clip;
	glm::vec4 ray_eye;
	glm::vec3 ray_world;
	CControls();
	~CControls();
	static CControls* m_pControls;
	CControls(CControls const&) = delete;//Deletes copy constructor
	void operator = (CControls const&) = delete;//Deletes the operator assgined to the copy constructor
};