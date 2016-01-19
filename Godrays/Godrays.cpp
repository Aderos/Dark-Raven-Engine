#include "Godrays.h"

Godrays::Godrays(OpenGL* m_OpenGL, ShaderManager* m_Shader) : vVertex(), vUV()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;
	this->m_Sun = new Object3D(m_OpenGL);
}

Godrays::~Godrays()
{
}

void Godrays::Initialize(int iWidth, int iHeight)
{	
	Build((float)iWidth, (float)iHeight);
	Bind();

	this->m_Sun->Initialize("../Assets/Sphere.obj");
	this->m_Sun->SetPosition(Vector3f(0.0f));
}

void Godrays::SetPosition(Vector3f vPosition)
{
	this->m_Sun->SetPosition(vPosition);
}

void Godrays::SetScale(Vector3f vScale)
{
	this->m_Sun->SetScale(vScale);
}

void Godrays::SetRotate(Vector3f vRotate)
{
	this->m_Sun->SetRotate(vRotate);
}

Vector3f Godrays::GetPosition()
{
	return this->m_Sun->GetPosition();
}

Vector3f Godrays::GetScale()
{
	return this->m_Sun->GetScale();
}

Vector3f Godrays::GetRotate()
{
	return this->m_Sun->GetRotate();
}

void Godrays::Build(float Width, float Height)
{
	float x = 0.5f;
	float y = 0.5f;

	//First triangle.
	this->vVertex.push_back(Vector3f(-x, y, 0)); // Top left.
	this->vVertex.push_back(Vector3f(x, -y, 0)); // Bottom right.
	this->vVertex.push_back(Vector3f(-x, -y, 0)); // Bottom left.

	this->vUV.push_back(Vector2f(0, 1));
	this->vUV.push_back(Vector2f(1, 0));
	this->vUV.push_back(Vector2f(0, 0));

	// Second triangle.
	this->vVertex.push_back(Vector3f(-x, y, 0)); // Top left.
	this->vVertex.push_back(Vector3f(x, y, 0)); // Top right.
	this->vVertex.push_back(Vector3f(x, -y, 0)); // Bottom right.

	this->vUV.push_back(Vector2f(0, 1));
	this->vUV.push_back(Vector2f(1, 1));
	this->vUV.push_back(Vector2f(1, 0));
}

void Godrays::Bind()
{
	this->m_OpenGL->GenVertexArrays(&iVAO);
	this->m_OpenGL->BindVertexArray(&iVAO);
	this->m_OpenGL->BindBufferData(iVertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
	this->m_OpenGL->BindBufferData(iUVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
}

void Godrays::SetTexture(GLuint iTexture)
{
	this->iTexture = iTexture;
}

void Godrays::SetDecay(double dDecay)
{
	this->dDecay = dDecay;
}

void Godrays::SetDensity(double dDensity)
{
	this->dDensity = dDensity;
}

void Godrays::SetExposure(double dExposure)
{
	this->dExposure = dExposure;
}

void Godrays::SetWeight(double dWeight)
{
	this->dWeight = dWeight;
}

void Godrays::SetColor(Vector3f vColor)
{
	this->vColor = vColor;
}

Vector3f Godrays::GetColor()
{
	return this->vColor;
}

void Godrays::DrawSun(Matrix44f mVP)
{
	this->m_Shader->UseShader(GLT_COLOR_SHADER, mVP * m_Sun->GetWorldMatrix(), Vector4f(vColor, 1.0f));
	this->m_Sun->Draw();
}

void Godrays::DrawGod(Matrix44f mVP, Vector3f vPos)
{
	m_Shader->UseShader(GLT_GODRAYS_SHADER, vPos, iTexture);
	
	this->m_OpenGL->BindVertexArray(&iVAO);
	this->m_OpenGL->DrawTriangles(0, vVertex.size());
}

void Godrays::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->DisableVertexAttribArray(3);
	this->m_OpenGL->ReleaseVertexArray(&iVAO);
	this->m_OpenGL->ReleaseTexture(iTexture);

	if (this->m_Sun)
	{
		this->m_Sun->Shutdown();
		delete this->m_Sun;
		this->m_Sun = 0;
	}
}