#include "Object2D.h"

Object2D::Object2D(OpenGL* m_OpenGL, ShaderManager* m_Shader) : vVertex(), vUV()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;
}

Object2D::~Object2D()
{
}

void Object2D::SetTexture(const char* cImagePath)
{
	this->iTexture = (new Texture(m_OpenGL))->GetTexture2D(cImagePath);
}

void Object2D::SetTexture(GLuint iTexture)
{
	this->iTexture = iTexture;
}

void Object2D::Initialize(int iX, int iY, int iWidth, int iHeight)
{
	Build((float)iX, (float)iY, (float)iWidth, (float)iHeight);
	Bind();
}

void Object2D::Build(float fX, float fY, float fWidth, float fHeight)
{
	this->vVertex.push_back(Vector3f(fX, fHeight + fY, 0.0f)); // Top left.
	this->vVertex.push_back(Vector3f(fWidth + fX, fY, 0.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(fX, fY, 0.0f)); // Bottom left.

	this->vUV.push_back(Vector2f(0.0f, 1.0f));
	this->vUV.push_back(Vector2f(1.0f, 0.0f));
	this->vUV.push_back(Vector2f(0.0f, 0.0f));

	this->vVertex.push_back(Vector3f(fX, fHeight + fY, 0.0f)); // Top left.
	this->vVertex.push_back(Vector3f(fWidth + fX, fHeight + fY, 0.0f)); // Top right.
	this->vVertex.push_back(Vector3f(fWidth + fX, fY, 0.0f)); // Bottom right.

	this->vUV.push_back(Vector2f(0.0f, 1.0f));
	this->vUV.push_back(Vector2f(1.0f, 1.0f));
	this->vUV.push_back(Vector2f(1.0f, 0.0f));
}

void Object2D::Reshape(int iX, int iY)
{
}

void Object2D::Bind()
{
	this->m_OpenGL->GenVertexArrays(&this->iVAO);
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->BindBufferData(this->iVertexBuffer, this->vVertex.size(), sizeof(Vector3f), &this->vVertex[0], 0, 3);
	this->m_OpenGL->BindBufferData(this->iUVBuffer, this->vUV.size(), sizeof(Vector2f), &this->vUV[0], 3, 2);
}

void Object2D::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->DisableVertexAttribArray(3);
	this->m_OpenGL->ReleaseVertexArray(&this->iVAO);
}

void Object2D::Draw()
{
	this->m_OpenGL->DisableDepth();

	this->m_Shader->UseShader(GLT_OBJECT_2D_SHADER, this->iTexture, (int)this->m_OpenGL->GetScreenWidth(), (int)this->m_OpenGL->GetScreenHeight());
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->DrawTriangles(0, this->vVertex.size());

	this->m_OpenGL->EnableDepth();
}