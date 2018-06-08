//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CControls.cpp
// Description	:	main implementation for CControls
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //

// This Includes //
#include <iostream>
#include "CControls.h"
#include "Utils.h"
#include "CCamera.h"
#include <glm\gtx\string_cast.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\matrix.hpp>

// Types //
using namespace std;
CControls* CControls::m_pControls; //Redefining the static variable for class
CControls::CControls()
{
}

CControls::~CControls()
{
}

CControls * CControls::GetInstance()
{
	if (!m_pControls)
	{
		m_pControls = new CControls();//creates an instance of controls
	}
	return m_pControls;
}

void CControls::DestroyInstance()
{
	if (m_pControls) //Checks to see if instance exists
	{
		delete m_pControls; //deletes instance
		m_pControls = nullptr;//set the pointer to nullptr
	}
}

void CControls::init()
{
	glutPassiveMotionFunc(MousePosPassive);
	glutKeyboardFunc(InitKeyDown);
	glutKeyboardUpFunc(InitKeyUp);
	for (int i = 0; i < 255; i++)
	{
		cKeyState[i] = INPUT_RELEASED;
	}
}

void CControls::update()
{
	float ix = (2.0f * mouseX) / (float)Utility::SCR_WIDTH - 1.0f;
	float iy = 1.0f - (2.0f * mouseY) / (float)Utility::SCR_HEIGHT;
	float iz = 1.0f;
	ray_nds = glm::vec3(ix, iy, iz);
	ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	ray_eye = glm::inverse(CCamera::GetInstance()->m_m4Proj) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	ray_world = glm::vec3(glm::inverse(CCamera::GetInstance()->m_m4View) * ray_eye);
	ray_world = glm::normalize(ray_world);
	//ray_world = (glm::vec3)ray_eye;

	std::cout << glm::to_string(ray_world) << std::endl;


	//std::cout << glm::to_string(ray_world) << std::endl;

	for (int i = 0; i < 255; i++)
	{
		if (cKeyState[i] == INPUT_FIRST_PRESSED)
		{
  			cKeyState[i] = INPUT_HOLD;
		}
		else if (cKeyState[i] == INPUT_FIRST_RELEASE)
		{
			cKeyState[i] = INPUT_RELEASED;
		}	
	
	}
	
}

void CControls::KeyDown(unsigned char cKey, int nX, int nY)
{
	cKeyState[cKey] = INPUT_FIRST_PRESSED;
}

void CControls::KeyUp(unsigned char cKey, int nX, int nY)
{
	cKeyState[cKey] = INPUT_FIRST_RELEASE;
}

void CControls::MousePosPassive(int x, int y)
{
	CControls::GetInstance()->MousePosUpdate(x,y);
}

void CControls::MousePosUpdate(int x, int y)
{
	mouseX = x;
	mouseY = y;
}


void CControls::InitKeyUp(unsigned char cKey, int nX, int nY)
{
	CControls::GetInstance()->KeyUp(cKey, nX, nY);
}
void CControls::InitKeyDown(unsigned char cKey, int nX, int nY)
{
	CControls::GetInstance()->KeyDown(cKey, nX, nY);
}

void CControls::Mouse(int nButton, int nGlutState, int nX, int nY)
{
	if (nButton < 3)
	{
		//Checking and tracking the mousees current button state
		cMouse[nButton] = (nGlutState == GLUT_DOWN)? INPUT_HOLD : INPUT_RELEASED;
	}
}



