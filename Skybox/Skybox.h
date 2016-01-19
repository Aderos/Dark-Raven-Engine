#pragma once

#include <vector>

#include "ShaderManager.h"
#include "Texture.h"
#include "OpenGL.h"

using std::vector;

class Skybox
{
public:
	Skybox(OpenGL* m_OpenGL, ShaderManager* m_Shader);
	~Skybox();

	void SetPosition(Vector3f vPosition);
	void SetRotate(Vector3f vRotate);
	void SetScale(Vector3f vScale);

	Vector3f GetPosition();
	Vector3f GetRotate();
	Vector3f GetScale();

	void Initialize(const char* cPosX, const char* cNegX, const char* cPosY, const char* cNegY, const char* cPosZ, const char* cNegZ);

	void Draw(Matrix44f mVP, double dOpacity);
	void Shutdown();

private:
	void Bind();
	void BuildCube();
	void BuildTexture(const char**);
	void BuildMatrix();

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;

private:
	Vector3f vPosition;
	Vector3f vRotate;
	Vector3f vScale;

	vector<Vector3f> vVertex;

	GLuint iVAO;
	GLuint iVertexBuffer;	
	GLuint iTexture;

	Matrix44f mWorldMatrix;

};