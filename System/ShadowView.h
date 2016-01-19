#ifndef _ShadowView_H_
#define _ShadowView_H_

#include <vector>

#include "ShaderManager.h"
#include "OpenGL.h"
#include "Math3D.h"
#include "Object.h"
#include "Texture.h"

using std::vector;
using Math::Vector2f;
using Math::Vector3f;

class ShadowView : Object
{
public:
	ShadowView(OpenGL*, ShaderManager*);
	~ShadowView();

	void SetTexture(const char*);
	void SetTexture(GLuint);
	void Initialize(int, int, int, int);
	void Shutdown();
	void Draw();
	void Reshape(int, int);

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;

private:
	vector<Vector3f> vVertex;
	vector<Vector2f> vUV;

	GLuint iVAO;
	GLuint iVertexBuffer;
	GLuint iUVBuffer;

	GLuint iTexture;

private:
	void Bind();
	void Build(float X, float Y, float Width, float Height);

};

#endif#pragma once
