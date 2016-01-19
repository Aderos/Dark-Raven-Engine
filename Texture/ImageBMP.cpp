#include "ImageBMP.h"

ImageBMP::ImageBMP(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->bmp = new BMP;
}

ImageBMP::~ImageBMP()
{
}

void ImageBMP::Load(const char* strImagePath)
{
	unsigned char header[54];

	FILE* file = fopen(strImagePath, "rb");
	if (!file)
	{
		std::cout << "Image could not be opened!/n";
		return;
	}
	if (fread(header, 1, 54, file) != 54)
	{
		std::cout << "Not a correct BMP file!\n";
		return;
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << "Not a correct BMP file!\n";
		return;
	}

	// Read ints from the byte array.
	this->bmp->iSize	= *(int*)&(header[0x22]);
	this->bmp->iWidth	= *(int*)&(header[0x12]);
	this->bmp->iHeight = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information.
	if (bmp->iSize == 0)
		bmp->iSize = bmp->iWidth * bmp->iHeight * 3;

	// Create a buffer.
	this->bmp->cData = new unsigned char[bmp->iSize];

	// Read the actual data from the file into the buffer.
	fread(bmp->cData, 1, bmp->iSize, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	this->bmp->iLevel = 0;
	this->bmp->iInternalFormat = m_OpenGL->GetRGB();
	this->bmp->iBorder = 0;
	this->bmp->iFormat = m_OpenGL->GetBGR();
	this->bmp->iType = m_OpenGL->GetUnsignedByte();
}

unsigned int ImageBMP::GetLevel()
{
	return this->bmp->iLevel;
}

unsigned int ImageBMP::GetInternalFormat()
{
	return this->bmp->iInternalFormat;
}

unsigned int ImageBMP::GetWidth()
{
	return this->bmp->iWidth;
}

unsigned int ImageBMP::GetHeight()
{
	return this->bmp->iHeight;
}

unsigned int ImageBMP::GetBorder()
{
	return this->bmp->iBorder;
}

unsigned int ImageBMP::GetFormat()
{
	return this->bmp->iFormat;
}

unsigned int ImageBMP::GetType()
{
	return this->bmp->iType;
}

unsigned char* ImageBMP::GetData()
{
	return this->bmp->cData;
}

void ImageBMP::Release()
{
	delete[] bmp->cData;
	this->bmp->cData = 0;
}

void ImageBMP::Shutdown()
{
	delete bmp;
	this->bmp = 0;
}