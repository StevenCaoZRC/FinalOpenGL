//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name	:	main.cpp
// Description	:	main implementation for program
// Author		:	Steven Zhao
// Mail			:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //
#include <iostream>
//#include <vld.h>

// Local Includes //
#include "CCamera.h"
#include "CSprite.h"
#include "CSceneManager.h" 
#include "CControls.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CInterface.h"
#include "CSound.h"

// OpenGl Includes //
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "ShaderLoader.h"
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include "TextureLoader.h"
#include "Utils.h"



// Types //
using namespace std;

// Prototypes //
void Update();
void render();
void exit();
int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(Utility::SCR_WIDTH, Utility::SCR_HEIGHT);
	glutCreateWindow("My Game");

	glewInit();
	CSceneManager::InstanceGet()->init();
	
	
	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutCloseFunc(exit);
	glutMainLoop();

	//CSceneManager::InstanceDestroy();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);//clears a colour
	CSceneManager::InstanceGet()->RenderCurrent();
	CInterface::InstanceGet()->render();
	glutSwapBuffers();
}
void exit()
{
	CSceneManager::InstanceDestroy();
	CCamera::InstanceDestroy();
	CControls::InstanceDestroy();
	CInterface::InstanceDestroy();
	CSound::InstanceDestroy();
	
}
void Update()
{
	// Update game information.
	glutPostRedisplay(); //render function is called
	CInterface::InstanceGet()->update();
	CSceneManager::InstanceGet()->UpdateCurrent();
	CControls::InstanceGet()->update();
}