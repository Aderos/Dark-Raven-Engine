#include "Logo.h"

Logo::Logo(OpenGL* m_OpenGL, ShaderManager* m_Shader)
{
	this->m_OpenGL = m_OpenGL;
	this->m_Obj2D = new Object2D(m_OpenGL, m_Shader);
}

Logo::~Logo()
{
}

void Logo::Initialize(int iX, int iY, int iWidth, int iHeight, const char* cImagePatch)
{
	this->m_Obj2D->Initialize(iX, iY, iWidth, iHeight);
	this->m_Obj2D->SetTexture(cImagePatch);
}

void Logo::Reshape(int iX, int iY)
{
	this->m_Obj2D->Reshape(iX, iY);
}

void Logo::Draw()
{
	this->m_OpenGL->EnableBlend();
	this->m_Obj2D->Draw();
	this->m_OpenGL->DisableBlend();
}

void Logo::Shutdown()
{
	if (this->m_Obj2D)
	{
		this->m_Obj2D->Shutdown();
		delete this->m_Obj2D;
		this->m_Obj2D = 0;
	}
}