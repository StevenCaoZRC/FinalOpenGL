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
	glutKeyboardFunc(InitKeyDown);
	glutKeyboardUpFunc(InitKeyUp);

}

void CControls::update()
{
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

