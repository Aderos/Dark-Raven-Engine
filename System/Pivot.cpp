#include "Pivot.h"

Pivot::Pivot(OpenGL* m_OpenGL, ShaderManager* m_Shader)
{
	this->m_OpenGL = m_OpenGL;;
	this->m_Shader = m_Shader;

	this->m_Obj[0] = new Object3D(this->m_OpenGL);
}

Pivot::~Pivot()
{
}

void Pivot::SetPosition(Vector3f a)
{
	this->m_Obj[0]->SetPosition(a);
}

Vector3f Pivot::GetPosition()
{
	return this->m_Obj[0]->GetPosition();
}

void Pivot::SetRotate(Vector3f a)
{
	this->m_Obj[0]->SetRotate(a);
}

Vector3f Pivot::GetRotate()
{
	return this->m_Obj[0]->GetRotate();
}

void Pivot::SetScale(Vector3f a)
{
	this->m_Obj[0]->SetScale(a);
}

Vector3f Pivot::GetScale()
{
	return this->m_Obj[0]->GetScale();
}

void Pivot::Initialize()
{
	this->m_Obj[0]->Initialize("../Assets/pivot.obj", "../Assets/pivot.bmp");
	this->m_Obj[0]->SetPosition(Vector3f(0.0f));
	this->m_Obj[0]->SetScale(Vector3f(1.0f));
	this->m_Obj[0]->SetRotate(Vector3f(0.0f));
}

void Pivot::Draw(Matrix44f mVP)
{
	m_Shader->UseShader(GLT_TEXTURE_SHADER, mVP * m_Obj[0]->GetWorldMatrix(), Vector4f(0.0f), m_Obj[0]->GetColorTexture());
	m_Obj[0]->Draw();
}

void Pivot::Shutdown()
{
	this->m_Obj[0]->Shutdown();
}