#include "Sphere.h"
#include "Utils.h"
#include "CCamera.h"
#include "TextureLoader.h"


Sphere::Sphere()
{
	float radius = 1.0f;

	const int sections = 20;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;

	float vertices[(sections) * (sections) * vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = cos(phi) * sin(theta);
			float y = cos(theta);
			float z = sin(phi) * sin(theta);

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


	GLuint indices[(sections) * (sections) * indexPerQuad];
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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

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
}



Sphere::~Sphere()
{
}

void Sphere::Render()
{
	glUseProgram(CUtility::program);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Activating the texture and binding it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[iCurrentFrame]);
	glUniform1i(glGetUniformLocation(CUtility::program, "tex"), 0);

	glBindVertexArray(VAO);			  // Bind VAO

	//------3D MVP------//
	glm::mat4 MVP = CCamera::GetInstance()->SetMVP3D(objPosition, objRotate, objScale);
	GLint MVPLoc = glGetUniformLocation(CUtility::program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	glDrawElements(DrawType, IndiceCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);			  // Unbind VAO

}
