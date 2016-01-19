#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <iostream>
#include <map>

#include "OpenGL.h"
#include "Image.h"
#include "ImageBMP.h"
#include "ImageTGA.h"

using std::map;
using std::string;

class Texture
{
public:
	Texture(OpenGL*);
	~Texture();

	GLuint GetTexture1D(GLubyte* uData);
	GLuint GetTexture2D(const char* sImagePath);
	GLuint GetTexture2DSkybox(const char** sImagePath);
	GLuint GenNewTexture2D(int x, int y);
	
	Image* GetTexture(const char* sImagePath);

private:
	OpenGL* m_OpenGL;
	map<string, Image*> mImage;
	
};

#endif