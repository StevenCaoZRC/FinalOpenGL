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

// Library Includes //

// Local Includes //

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
// This Includes //
#include "CSprite.h"
#include "Utils.h"
// Types //

using namespace std;

// Constructor //
////2D
//CSprite::CSprite(const char* _fileName, float fWidth, float fHeight)
//{
//	GLuint vbo;
//	GLuint ebo;
//	GLuint tex;
//
//	float HalfWidth = fWidth / 2;
//	float HalfHeight = fHeight / 2;
//	if (fWidth == 0 || fHeight == 0)
//	{
//		int nWidth, nHeight;
//		unsigned char* image = SOIL_load_image(
//			_fileName,				//File path/name
//			&nWidth,							//Output for the image width
//			&nHeight,						//Output for the image height
//			0,								//Output for number of channels
//			SOIL_LOAD_RGBA);
//		SOIL_free_image_data(image);
//
//		HalfWidth = nWidth;
//		HalfHeight = nHeight;
//	}
//	GLfloat vertices[36] = {
//		// Position			 //Colour			 //Tex Coords
//		-HalfWidth, HalfHeight, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // Top Left 
//		HalfWidth, HalfHeight, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // Top Right 
//		HalfWidth, -HalfHeight, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // Bottom Right 
//		-HalfWidth, -HalfHeight, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // Bottom Left
//	};
//	GLuint indices[6] =
//	{
//		0, 1, 2, // First Triangle 
//		0, 2, 3  // Second Triangle
//
//	};
//
//
//	TextureLoader textureloader;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER,
//		sizeof(vertices),
//		vertices,
//		GL_STATIC_DRAW);
//	glVertexAttribPointer(
//		0,						// Layout location on vertex shader
//		3,						// 3 float components (eg position)
//		GL_FLOAT,				// Type of data
//		GL_FALSE,				// Data Normalised?
//		8 * sizeof(GLfloat),	// Stride of the entire single vertex
//		(GLvoid*)0);			// Offset
//
//	glEnableVertexAttribArray(0);
//
//	// New AttribPointer for Colour
//	glVertexAttribPointer(
//		1,									// Layout location on vertex shader
//		3,									// 3 float components (eg position)
//		GL_FLOAT,							// Type of data
//		GL_FALSE,							// Data Normalised?
//		8 * sizeof(GLfloat),				// Stride of the entire single vertex
//		(GLvoid*)(3 * sizeof(GLfloat)));		// Offset
//	glEnableVertexAttribArray(1);
//
//	// EBO
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//		sizeof(indices),
//		indices,
//		GL_STATIC_DRAW);
//
//	glCullFace(GL_BACK); //Cull the back faces (basicly deletes the faces that are going in CCW)
//	glFrontFace(GL_CW);  //Front face is Clockwise order
//	//glEnable(GL_CULL_FACE);
//
//
//	glGenTextures(1, &tex);
//	glBindTexture(GL_TEXTURE_2D, tex);
//	//Texture class to load images.
//	textures.push_back(tex);
//
//	textureloader.TexImage2D(CSprite::nWidth, CSprite::nHeight, textureloader.imageloader(_fileName, CSprite::nWidth, CSprite::nHeight));
//
//	//Text Coord attribute pointer
//	glVertexAttribPointer(
//		2,			//Layout location on vertex shader
//		2,			//2 float components for texture coords
//		GL_FLOAT,    //Type of data
//		GL_FALSE,   //Data normalised?
//		8 * sizeof(GLfloat),		//Stride
//		(GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//}

CSprite::CSprite(const char* _fileName, float fWidth, float fHeight, int iShape)
{
	iObjectType = CUtility::NON_SOLID;
	GLuint vbo;
	GLuint ebo;
	m_iShape = iShape;
	TextureLoader textureloader;

	float HalfWidth = fWidth / 2;
	float HalfHeight = fHeight / 2;
	if (fWidth == 0 || fHeight == 0)
	{
		int nWidth, nHeight;
		unsigned char* image = SOIL_load_image(
			_fileName,				//File path/name
			&nWidth,							//Output for the image width
			&nHeight,						//Output for the image height
			0,								//Output for number of channels
			SOIL_LOAD_RGBA);
		SOIL_free_image_data(image);

		HalfWidth = (float)nWidth / 2;
		HalfHeight = (float)nHeight / 2;
		fRadius = (nWidth + nHeight) / 2;
	}

	switch (iShape)
	{
	case 0:
	{
		//-----------------------Going 3D-----------------------//
		GLfloat cubeVertices[] =
		{
		// Positions         // Colour       // Tex Coords
		// Front Face
		-HalfWidth,  HalfHeight,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 0
		HalfWidth,  HalfHeight,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // 1
		HalfWidth, -HalfHeight,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
		-HalfWidth, -HalfHeight,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // 3

		// Right Face
		HalfWidth,  HalfHeight,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 4
		HalfWidth,  HalfHeight, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 5
		HalfWidth, -HalfHeight, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 6
		HalfWidth, -HalfHeight,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 7

		// Back Face
		HalfWidth,  HalfHeight, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // 8
		-HalfWidth,  HalfHeight, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // 9
		-HalfWidth, -HalfHeight, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // 10
		HalfWidth, -HalfHeight, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // 11

		// Left Face
		-HalfWidth,  HalfHeight, -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 12
		-HalfWidth,  HalfHeight,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 13
		-HalfWidth, -HalfHeight,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 14
		-HalfWidth, -HalfHeight, -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 15

		// Top Face
		-HalfWidth,  HalfHeight, -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 16
		HalfWidth,  HalfHeight, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 17
		HalfWidth,  HalfHeight,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 18
		-HalfWidth,  HalfHeight,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 19

		// Bottom Face
		-HalfWidth, -HalfHeight,  1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 20
		HalfWidth, -HalfHeight,  1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 21
		HalfWidth, -HalfHeight, -1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // 22
		-HalfWidth, -HalfHeight, -1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 23
		};

		//GLfloat cubeVertices[] = {
		//	// Positions         // Normals         // Tex Coords
		//// Front Face
		//-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 0
		// 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 1
		// 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2
		//-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 3
		//// Right Face
		//1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 4
		//1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 5
		//1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 6
		//1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 7
		//// Back Face
		// 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // 8
		//-1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // 9
		//-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // 10
		// 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // 11
		//// Left Face
		//-1.0f,  1.0f, -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 12
		//-1.0f,  1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 13
		//-1.0f, -1.0f,  1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 14
		//-1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 15
		//// Top Face
		//-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 16
		// 1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 17
		// 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 18
		//-1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 19
		//// Bottom Face
		//-1.0f, -1.0f,  1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 20
		// 1.0f, -1.0f,  1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 21
		// 1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // 22
		//-1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // 23
		//};

		GLuint cubeIndices[] = {

			// Front Face	// Left Face
			0, 1, 2,		12, 13, 14,
			0, 2, 3,		12, 14, 15,

			// Right Face	// Top Face
			4, 5, 6,		16, 17, 18,
			4, 6, 7,		16, 18, 19,

			// Back Face	// Bottom Face
			8, 9, 10,		20, 21, 22,
			8, 10, 11,		20, 22, 23,
		};



		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(cubeVertices),
			cubeVertices,
			GL_STATIC_DRAW);
		glVertexAttribPointer(
			0,						// Layout location on vertex shader
			3,						// 3 float components (eg position)
			GL_FLOAT,				// Type of data
			GL_FALSE,				// Data Normalised?
			8 * sizeof(GLfloat),	// Stride of the entire single vertex
			(GLvoid*)0);			// Offset

		glEnableVertexAttribArray(0);

		// New AttribPointer for Colour
		glVertexAttribPointer(
			1,									// Layout location on vertex shader
			3,									// 3 float components (eg position)
			GL_FLOAT,							// Type of data
			GL_FALSE,							// Data Normalised?
			8 * sizeof(GLfloat),				// Stride of the entire single vertex
			(GLvoid*)(3 * sizeof(GLfloat)));		// Offset
		glEnableVertexAttribArray(1);

		// EBO
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(cubeIndices),
			cubeIndices,
			GL_STATIC_DRAW);


		//Face Culling / Depth testing
		glCullFace(GL_BACK); //Cull the back faces (basicly deletes the faces that are going in CCW)
		glFrontFace(GL_CW);  //Front face is Clockwise order
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		

		break;
	}
	case 1:
	{
		float radius = 1.0f;

		const int sections = 20;
		const int vertexAttrib = 8;
		const int indexPerQuad = 6;

		double phi = 0;
		double theta = 0;

		float vertices[(sections) * (sections)* vertexAttrib];
		int offset = 0;
		for (int i = 0; i < sections; i++)
		{
			theta = 0;

			for (int j = 0; j < sections; j++)
			{
				float x = (float)(cos(phi) * sin(theta));
				float y = (float)(cos(theta));
				float z = (float)(sin(phi) * sin(theta));

				vertices[offset++] = x * radius;
				vertices[offset++] = y * radius;
				vertices[offset++] = z * radius;

				vertices[offset++] = x;
				vertices[offset++] = y;
				vertices[offset++] = z;

				vertices[offset++] = (float)i / (sections - 1);
				vertices[offset++] = (float)j / (sections - 1);

				theta += (M_PI / (sections - 1));
			}

			phi += (2 * M_PI) / (sections - 1);
		}


		GLuint indices[(sections) * (sections)* indexPerQuad];
		offset = 0;
		for (int i = 0; i < sections; i++)
		{
			for (int j = 0; j < sections; j++)
			{
				indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
				indices[offset++] = (((i + 1) % sections) * sections) + (j);
				indices[offset++] = (i * sections) + (j);

				indices[offset++] = (i * sections) + ((j + 1) % sections);
				indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
				indices[offset++] = (i * sections) + (j);
			}
		}

		GLuint VBO, EBO;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		IndiceCount = sizeof(indices) / sizeof(GLuint);
		DrawType = GL_TRIANGLES;
		break;
	}
	default:
		break;
	}


	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//Texture class to load images.
	textures.push_back(tex);

	textureloader.TexImage2D(CSprite::nWidth, CSprite::nHeight, textureloader.imageloader(_fileName, CSprite::nWidth, CSprite::nHeight));

	//Text Coord attribute pointer
	glVertexAttribPointer(
		2,			//Layout location on vertex shader
		2,			//2 float components for texture coords
		GL_FLOAT,    //Type of data
		GL_FALSE,   //Data normalised?
		8 * sizeof(GLfloat),		//Stride
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

}
CSprite::~CSprite()
{

}

void CSprite::render()
{
	glUseProgram(CUtility::program);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Activating the texture and binding it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[iCurrentFrame]);
	glUniform1i(glGetUniformLocation(CUtility::program, "tex"), 0);

	glBindVertexArray(vao);			  // Bind VAO
	
	//------3D MVP------//
	glm::mat4 MVP = CCamera::GetInstance()->SetMVP(objPosition,objRotate,objScale);
	GLint MVPLoc = glGetUniformLocation(CUtility::program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);			  // Unbind VAO
	
}

void CSprite::update()
{

}

void CSprite::render3D()
{
	switch (m_iShape)
	{
	case 0:
	{
		glUseProgram(CUtility::program);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Activating the texture and binding it
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[iCurrentFrame]);
		glUniform1i(glGetUniformLocation(CUtility::program, "tex"), 0);

		glBindVertexArray(vao);			  // Bind VAO

										  //------3D MVP------//
		glm::mat4 MVP = CCamera::GetInstance()->SetMVP3D(objPosition, objRotate, objScale);
		GLint MVPLoc = glGetUniformLocation(CUtility::program, "MVP");
		glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

   		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);			  // Unbind VAO
		break;
	}
	case 1:
	{
		glUseProgram(CUtility::program);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Activating the texture and binding it
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(glGetUniformLocation(CUtility::program, "tex"), 0);

		glBindVertexArray(vao);			  // Bind VAO

										  //------3D MVP------//
		glm::mat4 MVP = CCamera::GetInstance()->SetMVP3D(objPosition, objRotate, objScale);
		GLint MVPLoc = glGetUniformLocation(CUtility::program, "MVP");
		glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		glDrawElements(GL_TRIANGLES, IndiceCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);			  // Unbind VAO
		break;
	}
	default:
		break;
	}
	
}

void CSprite::update3D()
{
}

void CSprite::addFrame(const char* _filename)
{
	GLuint tex;
	TextureLoader textureloader;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	//Texture class to load images.

	textureloader.TexImage2D(CSprite::nWidth, CSprite::nHeight, textureloader.imageloader(_filename, CSprite::nWidth, CSprite::nHeight));

	textures.push_back(tex);
}

void CSprite::ScaleSprite(float _scale)
{
	objScale * _scale;
	fRadius = fRadius * _scale;
}



