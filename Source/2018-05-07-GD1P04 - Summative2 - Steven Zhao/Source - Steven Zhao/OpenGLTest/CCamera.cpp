//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CCamera.cpp
// Description	:	main implementation for CCamera
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //

// This Includes //
#include "CCamera.h"

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;
CCamera* CCamera::m_pCamera;
// Constructor //
CCamera::CCamera()
{

}

// Destructor //
CCamera::~CCamera()
{

}

CCamera * CCamera::GetInstance()
{
	if (!m_pCamera) //if camera pointer doesnt exist
	{
		m_pCamera = new CCamera(); //Create an instance of Camera
	}
	return m_pCamera;
}

void CCamera::DestroyInstance()
{
	if (m_pCamera) //If a camera instance exists
	{
		delete m_pCamera; //Deletes pointer
		m_pCamera = nullptr;//Gets pointer to nullptr
	}
}

//------------------------------| Getting MVP Matrices |-------------------------------//
glm::mat4 CCamera::SetMVP(glm::vec3 v3_SetTranslation, glm::vec3 v3_SetRotation, glm::vec3 v3_SetScale)
{
	m_m4Translate = glm::translate(glm::mat4(), v3_SetTranslation);
	m_m4Rotate = glm::rotate(glm::mat4(), glm::radians(v3_SetRotation.z), glm::vec3(0, 0, 1)); //Z
	m_m4Scale = glm::scale(glm::mat4(), v3_SetScale);
	//Model Matrix
	m_m4Model = m_m4Translate * m_m4Rotate *m_m4Scale;

	//view
	m_m4View = glm::lookAt(m_v3CameraPos, m_v3CameraPos + m_v3CameraForward, m_v3CameraUp);

	//Projection and Camera
	float fHalfScrWidth = (float)Utility::SCR_WIDTH/2;  
	float fHalfScrHeight = (float)Utility::SCR_HEIGHT/2;
	m_m4Proj = glm::ortho(-fHalfScrWidth, fHalfScrWidth, -fHalfScrHeight, fHalfScrHeight, 0.1f, 100.0f); 
	m_m4MVP = m_m4Proj * m_m4View * m_m4Model;
	return m_m4MVP;
}

glm::mat4 CCamera::SetMVP3D(glm::vec3 v3_SetTranslation, glm::vec3 v3_SetRotation, glm::vec3 v3_SetScale)
{
	m_m4Translate = glm::translate(glm::mat4(), v3_SetTranslation);
	m_m4Rotate = glm::rotate(glm::mat4(), glm::radians(v3_SetRotation.y), glm::vec3(0.0f, 0.0f, 1.0f)); //Z
	m_m4Scale = glm::scale(glm::mat4(), v3_SetScale);
	//Model Matrix
	m_m4Model = m_m4Translate * m_m4Rotate *m_m4Scale;

	//view
	m_m4View = glm::lookAt(glm::vec3(m_v3CamX, m_v3CamHeight ,m_v3CamZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//Projection and Camera
	m_m4Proj = glm::perspective(45.0f, (float)Utility::SCR_WIDTH / (float)Utility::SCR_HEIGHT, 0.1f, 10000.0f);

	//MVP
	m_m4MVP = m_m4Proj * m_m4View * m_m4Model;
	return m_m4MVP;
}

