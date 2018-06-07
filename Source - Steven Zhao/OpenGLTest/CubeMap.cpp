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
#include "Utils.h"
#include <string>
CCubeMap::CCubeMap(std::vector<std::string> _filePaths)
{
	static ShaderLoader shaderl;
	cubemapProgram = shaderl.CreateProgram("CubeMapVer.txt", "CubeMapFrag.txt");


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

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	int iWidth, iHeight;
	unsigned char* image;

	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/CubeMap/";
		fullPathName.append(_filePaths[i]);

		image = SOIL_load_image(fullPathName.c_str(), &iWidth, &iHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

CCubeMap::~CCubeMap()
{
}

void CCubeMap::render()
{
	glUseProgram(cubemapProgram);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glUniform1i(glGetUniformLocation(cubemapProgram, "skybox"), 0);

	glm::mat4 MVP = CCamera::GetInstance()->SetMVP3D(objPosition, objRotate, objScale);
	glUniformMatrix4fv(glGetUniformLocation(cubemapProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	// Bind the VAO and draw the cube map
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	// Clean up after render
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
