#include "Frame.h"

Frame::Frame(OpenGL* m_OpenGL, ShaderManager* m_Shader) : vVertex(), vUV()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;
}

Frame::~Frame()
{
}

void Frame::SetTexture(const char* cImagePath)
{
	this->iTexture = (new Texture(m_OpenGL))->GetTexture2D(cImagePath);
}

void Frame::SetTexture(GLuint iTexture)
{
	this->iTexture = iTexture;
}

void Frame::Initialize(int iX, int iY, int iWidth, int iHeight)
{
	Build((float)iX, (float)iY, (float)iWidth, (float)iHeight);
	Bind();
}

void Frame::Build(float fX, float fY, float fWidth, float fHeight)
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

void Frame::Reshape(int iX, int iY)
{
}

void Frame::Bind()
{
	this->m_OpenGL->GenVertexArrays(&this->iVAO);
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->BindBufferData(this->iVertexBuffer, this->vVertex.size(), sizeof(Vector3f), &this->vVertex[0], 0, 3);
	this->m_OpenGL->BindBufferData(this->iUVBuffer, this->vUV.size(), sizeof(Vector2f), &this->vUV[0], 3, 2);
}

void Frame::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->DisableVertexAttribArray(3);
	this->m_OpenGL->ReleaseVertexArray(&this->iVAO);
}

void Frame::Draw(GLuint iTexture)
{
	this->m_OpenGL->DisableDepth();

	this->m_Shader->UseShader(GLT_FRAME_SHADER, this->iTexture);

	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->DrawTriangles(0, this->vVertex.size());

	this->m_OpenGL->EnableDepth();
}