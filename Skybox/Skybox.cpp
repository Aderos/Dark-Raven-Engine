#include "Skybox.h"

Skybox::Skybox(OpenGL* m_OpenGL, ShaderManager* m_Shader) : vVertex()
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;

	this->mWorldMatrix = Matrix44f(0.0f);

	this->vPosition = Vector3f(0.0f);
	this->vRotate = Vector3f(0.0f);
	this->vScale = Vector3f(50.0f);
	
	this->iVAO = 0;
	this->iVertexBuffer = 0;
	this->iTexture = 0;
}

Skybox::~Skybox()
{
}

void Skybox::SetPosition(Vector3f vPosition)
{
	this->vPosition = vPosition;
	BuildMatrix();
}

void Skybox::SetRotate(Vector3f vRotate)
{
	this->vRotate = vRotate;
	BuildMatrix();
}

void Skybox::SetScale(Vector3f vScale)
{
	this->vScale;
	BuildMatrix();
}

Vector3f Skybox::GetPosition()
{
	return this->vPosition;
}

Vector3f Skybox::GetRotate()
{
	return this->vRotate;
}

Vector3f Skybox::GetScale()
{
	return this->vScale;
}

void Skybox::Initialize(const char* cPosX, const char* cNegX, const char* cPosY, const char* cNegY, const char* cPosZ, const char* cNegZ)
{
	BuildTexture(new const char*[6] { cPosX, cNegX, cPosY, cNegY, cPosZ, cNegZ });
	BuildMatrix();
	BuildCube();
	Bind();
}

void Skybox::BuildTexture(const char** cSkyboxTextures)
{
	this->iTexture = (new Texture(this->m_OpenGL))->GetTexture2DSkybox(cSkyboxTextures);
}

void Skybox::BuildCube()
{
	// Front
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, 1.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, 1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, 1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, 1.0f)); // Bottom right.

	// Right
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, -1.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, 1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(1.0f, 1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, -1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, -1.0f)); // Bottom right.

	// Left
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, 1.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, -1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, 1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, 1.0f)); // Bottom right.

	// Back
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, -1.0f)); // Bottom right.ol
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, -1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, -1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, -1.0f)); // Bottom right.

	// Top
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, 1.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, 1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(-1.0f, 1.0f, -1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, -1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(1.0f, 1.0f, 1.0f)); // Bottom right.

	// Bottom
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, -1.0f)); // Bottom right.
	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, -1.0f)); // Bottom left.

	this->vVertex.push_back(Vector3f(-1.0f, -1.0f, 1.0f)); // Top left.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, 1.0f)); // Top right.
	this->vVertex.push_back(Vector3f(1.0f, -1.0f, -1.0f)); // Bottom right.
}

void Skybox::BuildMatrix()
{
	Matrix44f mWorldScale = Math::Scale(vScale);
	Matrix44f mWorldRotate = Math::Rotate(vRotate);
	Matrix44f mWorldTranslation = Math::Translation(vPosition);

	this->mWorldMatrix = mWorldTranslation * mWorldRotate * mWorldScale;
}

void Skybox::Bind()
{
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->BindBufferData(this->iVertexBuffer, this->vVertex.size(), sizeof(Vector3f), &this->vVertex[0], 0, 3);
	this->m_OpenGL->BindActiveCubeMap(this->iTexture);
}

void Skybox::Draw(Matrix44f mVP, double dOpacity)
{
	this->m_OpenGL->EnableBlend();
	
	Matrix44f mMVP = mVP * this->mWorldMatrix;

	this->m_Shader->UseShader(GLT_SKYBOX_SHADER, mMVP, this->iTexture, dOpacity);

	this->m_OpenGL->BindActiveCubeMap(this->iTexture);
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->DrawTriangles(0, this->vVertex.size());

	this->m_Shader->Reset();

	this->m_OpenGL->DisableBlend();
}

void Skybox::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->ReleaseVertexArray(&this->iVAO);
	this->m_OpenGL->ReleaseTexture(this->iTexture);
}