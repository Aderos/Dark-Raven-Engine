#ifndef _IMAGETGA_H_
#define _IMAGETGA_H_

#include <iostream>

#include "OpenGL.h"
#include "Image.h"

class ImageTGA : Image
{
private:
	struct TGA
	{
		unsigned int	iLevel;
		unsigned int	iInternalFormat;
		unsigned short	iWidth;
		unsigned short	iHeight;
		unsigned int	iBorder;
		unsigned int	iFormat;
		unsigned int	iType;
		unsigned int	iSize;
		unsigned char*	cData;
		unsigned char	cIdentsize;
		unsigned char	cColorMapType;
		unsigned char	cImageType;
		unsigned short	iColorMapStart;
		unsigned short	iColorMapLength;
		unsigned char 	cColorMapBits;
		unsigned short	iXstart;
		unsigned short	iYstart;
		unsigned char	cBits;
		unsigned char	cDescriptor;
	};

public:
	ImageTGA(OpenGL*);
	~ImageTGA();

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
	TGA* tga;

};

#endif