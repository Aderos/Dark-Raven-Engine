#include "Grid.h"

Grid::Grid(OpenGL* m_OpenGL, ShaderManager* m_Shader) : vVertex()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;

	this->iVAO = 0;
	this->iVertexBuffer = 0;

	this->mWorldMatrix = 0;

	this->vPosition = Vector3f(0.0f);
	this->vScale = Vector3f(1.0f);
	this->vRotate = Vector3f(0.0f);
}

Grid::~Grid()
{
}

void Grid::SetPosition(Vector3f a)
{
	this->vPosition = a;
	BuildWorldMatrix();
}

Vector3f Grid::GetPosition()
{
	return this->vPosition;
}

void Grid::SetRotate(Vector3f a)
{
	this->vRotate = a;
	BuildWorldMatrix();
}

Vector3f Grid::GetRotate()
{
	return this->vRotate;
}

void Grid::SetScale(Vector3f a)
{
	this->vScale = a;
	BuildWorldMatrix();
}

Vector3f Grid::GetScale()
{
	return this->vScale;
}

Matrix44f Grid::GetWorldMatrix()
{
	return this->mWorldMatrix;
}

void Grid::BuildWorldMatrix()
{
	Matrix44f mWorldScale = Math::Scale(vScale);
	Matrix44f mWorldRotate = Math::Rotate(vRotate);
	Matrix44f mWorldTranslation = Math::Translation(vPosition);

	this->mWorldMatrix = mWorldTranslation * mWorldRotate * mWorldScale;
}

void Grid::Initialize()
{
	for (float i = -8; i <= 8; i+=1.0f)
	{
		this->vVertex.push_back(Vector3f(i, 0.0f, -8.0f));
		this->vVertex.push_back(Vector3f(i, 0.0f,  8.0f));

		this->vVertex.push_back(Vector3f(-8.0f, 0.0f, i));
		this->vVertex.push_back(Vector3f( 8.0f, 0.0f, i));
	}

	Bind();
}

void Grid::Bind()
{
	this->m_OpenGL->GenVertexArrays(&iVAO);
	this->m_OpenGL->BindVertexArray(&iVAO);
	this->m_OpenGL->BindBufferData(iVertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
}

void Grid::Draw(Matrix44f mVP)
{
	Matrix44f mMVP = mVP * mWorldMatrix;
	
	this->m_Shader->UseShader(GLT_COLOR_SHADER, mMVP, Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
	this->m_OpenGL->BindVertexArray(&iVAO);
	this->m_OpenGL->DrawLines(0, vVertex.size());
}

void Grid::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->ReleaseVertexArray(&iVAO);
}