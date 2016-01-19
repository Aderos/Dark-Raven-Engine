#include "Texture.h"

Texture::Texture(OpenGL* m_OpenGL) : mImage()
{
	this->m_OpenGL = m_OpenGL;

	this->mImage["bmp"] = (Image*)new ImageBMP(m_OpenGL);
	this->mImage["tga"] = (Image*)new ImageTGA(m_OpenGL);
}

Texture::~Texture()
{
	this->mImage["bmp"]->Release();
	this->mImage["bmp"]->Shutdown();
	delete mImage["bmp"];

	this->mImage["tga"]->Release();
	this->mImage["tga"]->Shutdown();
	delete mImage["tga"];

}

GLuint Texture::GetTexture1D(GLubyte* uData)
{
	GLuint iTexture = 0;
	
	this->m_OpenGL->BindTexture1D(iTexture, 4, uData);

	return iTexture;
}

GLuint Texture::GetTexture2D(const char* sImagePath)
{
	GLuint iTexture = 0;

	int size = strlen(sImagePath);

	Image* image = 0;

	string extension{};
	extension.append(1, sImagePath[size - 3]);
	extension.append(1, sImagePath[size - 2]);
	extension.append(1, sImagePath[size - 1]);

	(image = this->mImage[extension])->Load(sImagePath);

	this->m_OpenGL->BindTexture2D(iTexture, image->GetLevel(), image->GetInternalFormat(), image->GetWidth(),
		image->GetHeight(), image->GetBorder(), image->GetFormat(), image->GetType(), image->GetData());

	if (image)
	{
		delete image;
		image = 0;
	}

	return iTexture;
}

GLuint Texture::GetTexture2DSkybox(const char** skyboxTextures)
{
	GLuint iTexture = 0;

	this->m_OpenGL->BindTextureCubeMap(iTexture);

	GLenum  cube[6] = {	
		this->m_OpenGL->GetTextureCubeMapPosX(), 
		this->m_OpenGL->GetTextureCubeMapNegX(),
		this->m_OpenGL->GetTextureCubeMapPosY(), 
		this->m_OpenGL->GetTextureCubeMapNegY(),
		this->m_OpenGL->GetTextureCubeMapPosZ(), 
		this->m_OpenGL->GetTextureCubeMapNegZ() };

	for (int i = 0; i < 6; ++i)
	{
		Image* image = GetTexture(skyboxTextures[i]);

		this->m_OpenGL->BindPartTextureCubeMap(cube[i], image->GetLevel(), image->GetInternalFormat(), image->GetWidth(),
			image->GetHeight(), image->GetBorder(), image->GetFormat(), image->GetType(), image->GetData());
	}

	return iTexture;
}

Image* Texture::GetTexture(const char* strImagePath)
{
	int size = strlen(strImagePath);

	Image* image = 0;

	string extension{};
	extension.append(1, strImagePath[size - 3]);
	extension.append(1, strImagePath[size - 2]);
	extension.append(1, strImagePath[size - 1]);

	(image = this->mImage[extension])->Load(strImagePath);

	return image;
}

GLuint Texture::GenNewTexture2D(int iX, int iY)
{
	GLuint texHandle;
	glGenTextures(1, &texHandle);

	m_OpenGL->glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 512, 512, 0, GL_RED, GL_FLOAT, NULL);

	m_OpenGL->glBindImageTexture(0, texHandle, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);
	
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error in \"%s\": %s (%d)\n", "gen tex", gluErrorString(e), e);
		return 0;
	}
	
	return texHandle;
}