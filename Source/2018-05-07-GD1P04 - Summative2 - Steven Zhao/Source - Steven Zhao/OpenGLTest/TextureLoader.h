#pragma once
#include "glew.h"
#include "freeglut.h"
#include "SOIL.h"
#include <string>

class TextureLoader
{
public:
	//Generating texture and binding
	
	unsigned char* imageloader(const char* _TexturefileName, int &width, int &height)
	{
		unsigned char* image = SOIL_load_image(
			_TexturefileName,				//File path/name
			&width,							//Output for the image width
			&height,						//Output for the image height
			0,								//Output for number of channels
			SOIL_LOAD_RGBA);				//Load RGB values only
		return (image);
	};

	void TexImage2D(int &width, int &height, unsigned char* image)
	{
		glTexImage2D(
			GL_TEXTURE_2D,			//Type of texture
			0,						//MipMap level, 0 for base
			GL_RGBA,	  			//Number of color components in texture
			width,					//Width of the texture
			height,					//Height of the texture
			0,						//This value must be 0
			GL_RGBA,				//Format for the pixel data
			GL_UNSIGNED_BYTE,		//Data type of the pixel data
			image					//Pointer to image data in memory
		);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

	};
};