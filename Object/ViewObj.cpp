#include "ViewObj.h"

ViewObj::ViewObj(OpenGL* m_OpenGL) : vVertex(), vUV()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = new ShaderManager(m_OpenGL);
	this->m_Texture = new Texture(m_OpenGL);
}

ViewObj::~ViewObj()
{
}

void ViewObj::SetTexture(const char* strImagePath)
{
	this->TextureID = m_Texture->GetTexture2D(strImagePath);
}

void ViewObj::SetTexture(GLuint TextureID)
{
	this->TextureID = TextureID;
}

void ViewObj::Initialize(int X, int Y, int Width, int Height)
{
	this->m_Shader->Initialize();
	Build((float)X, (float)Y, (float)Width, (float)Height);
	Bind();
}

void ViewObj::Build(float X, float Y, float Width, float Height)
{
	//First triangle.
	vVertex.push_back(Vector3f(X, Height + Y, 0)); // Top left.
	vVertex.push_back(Vector3f(Width + X, Y, 0)); // Bottom right.
	vVertex.push_back(Vector3f(X, Y, 0)); // Bottom left.

	vUV.push_back(Vector2f(0, 1));
	vUV.push_back(Vector2f(1, 0));
	vUV.push_back(Vector2f(0, 0));

	// Second triangle.
	vVertex.push_back(Vector3f(X, Height + Y, 0)); // Top left.
	vVertex.push_back(Vector3f(Width + X, Height + Y, 0)); // Top right.
	vVertex.push_back(Vector3f(Width + X, Y, 0)); // Bottom right.

	vUV.push_back(Vector2f(0, 1));
	vUV.push_back(Vector2f(1, 1));
	vUV.push_back(Vector2f(1, 0));
}

void ViewObj::Reshape(int X, int Y)
{
}

void ViewObj::Bind()
{
	m_OpenGL->GenVertexArrays(&VertexArrayObject);
	m_OpenGL->BindVertexArray(&VertexArrayObject);
	m_OpenGL->BindBufferData(VertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
	m_OpenGL->BindBufferData(UVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
}

void ViewObj::Shutdown()
{
	m_OpenGL->DisableVertexAttribArray(0);
	m_OpenGL->DisableVertexAttribArray(3);
	m_OpenGL->ReleaseVertexArray(&VertexArrayObject);
}

void ViewObj::SetDecay(double decay)
{
	this->cay = decay;
}

void ViewObj::SetDensity(double density)
{
	this->density = density;
}

void ViewObj::SetExposure(double exposure)
{
	this->exposure = exposure;
}

void ViewObj::SetWeight(double weight)
{
	this->weight = weight;
}

void ViewObj::SetPosition(float x, float y)
{
	this->vPosition = Vector2f(x, y);
}

void ViewObj::Draw()
{
	//glDisable(GL_DEPTH_TEST);
	m_Shader->UseShader(GLT_GODRAYS_SHADER, TextureID, (int)m_OpenGL->GetScreenWidth(), (int)m_OpenGL->GetScreenHeight(), exposure, cay, density, weight, vPosition);
	m_OpenGL->BindVertexArray(&VertexArrayObject);
	m_OpenGL->DrawTriangles(0, vVertex.size());
	//glEnable(GL_DEPTH_TEST);
}