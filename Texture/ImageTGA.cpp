#include "ImageTGA.h"

ImageTGA::ImageTGA(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->tga = new TGA;
}

ImageTGA::~ImageTGA()
{
}

void ImageTGA::Load(const char* strImagePath)
{
	int iDepth;
	unsigned long lImageSize;

	this->tga = new TGA;

	FILE* file = fopen(strImagePath, "rb");
	if (!file)
	{
		std::cout << "Image could not be opened!\n";
		return;
	}

	fread(&tga->cIdentsize, sizeof(unsigned char), 1, file);
	fread(&tga->cColorMapType, sizeof(unsigned char), 1, file);
	fread(&tga->cImageType, sizeof(unsigned char), 1, file);
	fread(&tga->iColorMapStart, sizeof(short int), 1, file);
	fread(&tga->iColorMapLength, sizeof(short int), 1, file);
	fread(&tga->cColorMapBits, sizeof(unsigned char), 1, file);
	fread(&tga->iXstart, sizeof(short int), 1, file);
	fread(&tga->iYstart, sizeof(short int), 1, file);
	fread(&tga->iWidth, sizeof(short int), 1, file);
	fread(&tga->iHeight, sizeof(short int), 1, file);
	fread(&tga->cBits, sizeof(unsigned char), 1, file);
	fread(&tga->cDescriptor, sizeof(unsigned char), 1, file);

	if (tga->cBits != 8 && tga->cBits != 24 && tga->cBits != 32)
		return;

	// Color mode -> 3 = BGR, 4 = BGRA.
	iDepth = tga->cBits / 8;
	lImageSize = tga->iWidth * tga->iHeight * iDepth;

	this->tga->cData = new unsigned char[lImageSize];

	// Read the image data.
	fread(tga->cData, lImageSize, 1, file);

	GLenum eFormat = m_OpenGL->GetBGR();
	GLint iComponents = m_OpenGL->GetRGB();

	// Set OpenGL format expected
	switch (iDepth)
	{
	case 1:
		eFormat = m_OpenGL->GetLuminance();
		iComponents = m_OpenGL->GetLuminance();
		break;
	case 4:
		eFormat = m_OpenGL->GetBGRA();
		iComponents = m_OpenGL->GetRGBA();
		break;
	}

	// Done with File
	fclose(file);

	this->tga->iLevel = 0;
	this->tga->iInternalFormat = iComponents;
	this->tga->iBorder = 0;
	this->tga->iFormat = eFormat;
	this->tga->iType = m_OpenGL->GetUnsignedByte();
}

unsigned int ImageTGA::GetLevel()
{
	return this->tga->iLevel;
}

unsigned int ImageTGA::GetInternalFormat()
{
	return this->tga->iInternalFormat;
}

unsigned int ImageTGA::GetWidth()
{
	return this->tga->iWidth;
}

unsigned int ImageTGA::GetHeight()
{
	return this->tga->iHeight;
}

unsigned int ImageTGA::GetBorder()
{
	return this->tga->iBorder;
}

unsigned int ImageTGA::GetFormat()
{
	return this->tga->iFormat;
}

unsigned int ImageTGA::GetType()
{
	return this->tga->iType;
}

unsigned char* ImageTGA::GetData()
{
	return this->tga->cData;
}

void ImageTGA::Release()
{
	delete[] tga->cData;
	this->tga->cData = 0;
}

void ImageTGA::Shutdown()
{
	delete tga;
	this->tga = 0;
}