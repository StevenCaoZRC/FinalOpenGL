#pragma once

#include "glew.h"
#include "freeglut.h"
#include <map>
#include <iostream>
struct sProgram
{
	const char* _kVS;
	const char* _kFS;
};

class ShaderLoader
{
	private:
		std::string ReadShader(const char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			const char* shaderName);
		std::map<const char*, GLuint> m_mShaderMap;
		std::map<sProgram*, GLuint> m_mProgramMap;
	public:

		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(const char* VertexShaderFilename,
			const char* FragmentShaderFilename);

};
