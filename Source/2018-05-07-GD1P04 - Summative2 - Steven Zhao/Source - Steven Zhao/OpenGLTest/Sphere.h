#pragma once

#include <glew.h>
#include <freeglut.h>
#include "CSprite.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Sphere
{
public:
	Sphere();
	~Sphere();

	void Render();
	 
private:
	GLuint VAO;

	GLuint IndiceCount;
	int DrawType;
	std::vector<GLuint> textures;
	//GLuint tex1;
	//GLuint tex2;

	int iCurrentFrame = 0;

	glm::vec3 objPosition = { 0.0f,0.0f,0.0f };
	glm::vec3 objRotate = { 0.0f,0.0f,0.0f };
	glm::vec3 objScale = { 1.0f,1.0f,1.0f };
};

