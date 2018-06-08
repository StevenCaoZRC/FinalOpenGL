//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	CCamera.h
// Description	:	header file outlining the CCamera
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

#pragma once

#ifndef _CCAMERA_H__
#define _CCAMERA_H__

// Library Includes //
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "ShaderLoader.h"
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include "TextureLoader.h"
#include "Utils.h" 


class CCamera
{
        public:
			static CCamera* GetInstance();
			static void DestroyInstance();

			//---------------| Getting MVP Matrices for 2D|---------------//
			glm::mat4 SetMVP(glm::vec3 v3_SetTranslation, glm::vec3 v3_SetRotation, glm::vec3 v3_SetScale);
		
			glm::vec3 m_v3CameraPos = glm::vec3(0.0f, 0.0f, 400.0f);
			glm::vec3 m_v3CameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 m_v3CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

			//---------------| Getting MVP Matrices for 3D|---------------//
			glm::mat4 SetMVP3D(glm::vec3 v3_SetTranslation, glm::vec3 v3_SetRotation, glm::vec3 v3_SetScale);
			
			static CCamera* m_pCamera;
			CCamera();
			~CCamera();
			CCamera(CCamera const&) = delete; //Deletes copy constructor
			void operator = (CCamera const&) = delete; //Deletes operator assigned to the copy constructor		
	
			//---------------| Matrices for MVP |---------------//
			glm::mat4 m_m4Proj;
			glm::mat4 m_m4Model;
			glm::mat4 m_m4View;
			glm::mat4 m_m4MVP;
			glm::mat4 m_m4Scale;
			glm::mat4 m_m4Translate;
			glm::mat4 m_m4Rotate;
			
};

#endif // _CCAMERA_H__

