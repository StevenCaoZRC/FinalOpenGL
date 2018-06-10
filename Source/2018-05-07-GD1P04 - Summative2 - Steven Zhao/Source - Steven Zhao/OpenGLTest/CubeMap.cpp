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
	//Program which contains the vertex shader and fragment shader for the cubemaping
	static ShaderLoader shaderl;
	cubemapProgram = shaderl.CreateProgram("Resources/Shaders/VertexShaders/CubeMapVert.txt", "Resources/Shaders/FragmentShaders/CubeMapFrag.txt");

	//Cube vertices that only contain the position 
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

	//Cub indices
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

	//Generating the texture specifing number of textures generated and stores in tex
	glGenTextures(1, &tex);
	//Binding texture stored to target
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	int iWidth, iHeight;
	unsigned char* image;

	//Loop, going through creating six textures and loading an image on to each using SOIL
	for (GLuint i = 0; i < 6; i++)
	{
		//Prevent repetition in code
		std::string fullPathName = "Resources/ame_nebula/";

		fullPathName.append(_filePaths[i]);

		image = SOIL_load_image(fullPathName.c_str(), &iWidth, &iHeight, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

	}

	//Texture parameters, making sure we also do texture wrapping on the x axis
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	//X
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	//Y
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);	//Z
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
	//Using the cubemapProgram which had cubemap vertex and frag shaders
	glUseProgram(cubemapProgram);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glUniform1i(glGetUniformLocation(cubemapProgram, "skybox"), 0);

	glm::mat4 MVP = CCamera::GetInstance()->SetMVP3D(objPosition, objRotate, glm::vec3(1000.0f, 1000.0f, 1000.0f));
	glUniformMatrix4fv(glGetUniformLocation(cubemapProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	// Bind the VAO and draw the cube map
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	// Clean up after render
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
