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
#include <time.h>
#include <math.h>
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

#define FPS 60

// Types //
using namespace std;

// Prototypes //
void Update(int);
void render();
void exit();
auto initialTime = time(NULL);
auto finalTime = time(NULL);
int frameCount = 0;
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(Utility::SCR_WIDTH, Utility::SCR_HEIGHT);
	glutCreateWindow("My Game");

	glewInit();
	CSceneManager::GetInstance()->init();
	
	glutDisplayFunc(render);
	glutTimerFunc(1000/FPS, Update,0);
	glutCloseFunc(exit);
	glutMainLoop();

	
}

void render()
{
	//2D
	glClear(GL_COLOR_BUFFER_BIT);
	//3D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);//clears a colour

	CSceneManager::GetInstance()->RenderCurrent();

	//FPS 
	if (frameCount != 60)
		frameCount++;

	finalTime = time(NULL);
	if (finalTime - initialTime > 0)
	{
		cout << "FPS: " << frameCount / (finalTime - initialTime) << endl;
		CInterface::GetInstance()->FPSCounter.SetText("FPS: " + std::to_string(frameCount / (finalTime - initialTime)));
		frameCount = 0;
		initialTime = finalTime;
	}
	
	CInterface::GetInstance()->FPSCounter.Render();
	glutSwapBuffers();
	
}
void exit()
{
	CSceneManager::DestroyInstance();
	CCamera::DestroyInstance();
	CControls::DestroyInstance();
	CInterface::DestroyInstance();
	CSound::DestroyInstance();
}
void Update(int)
{
	// Update game information.
	glutPostRedisplay(); //render function is called
	glutTimerFunc( ( 1000 / 60), Update, 0);
	CInterface::GetInstance()->update();
	CSceneManager::GetInstance()->UpdateCurrent();
	CControls::GetInstance()->update();
	
}