#ifndef _IMAGEBMP_H_
#define _IMAGEBMP_H_

#include <iostream>

#include "OpenGL.h"
#include "Image.h"

class ImageBMP : Image
{
private:
	struct BMP
	{
		unsigned int   iLevel;
		unsigned int   iInternalFormat;
		unsigned int   iWidth;
		unsigned int   iHeight;
		unsigned int   iBorder;
		unsigned int   iFormat;
		unsigned int   iType;
		unsigned int   iSize;
		unsigned char* cData;
	};

public:
	ImageBMP(OpenGL*);
	~ImageBMP();

	void Load(const char*);

	unsigned int GetLevel();
	unsigned int GetInternalFormat();
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetBorder();
	unsigned int GetFormat();
	unsigned int GetType();
	unsigned char* GetData();

	void Release();
	void Shutdown();

private:
	OpenGL* m_OpenGL;
	BMP* bmp;

};

#endif