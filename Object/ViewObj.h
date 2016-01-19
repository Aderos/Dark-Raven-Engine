#ifndef _ViewObj_H_
#define _ViewObj_H_

#include <vector>

#include "ShaderManager.h"
#include "OpenGL.h"
#include "Math3D.h"
#include "Object.h"
#include "Texture.h"

using std::vector;
using Math::Vector2f;
using Math::Vector3f;

class ViewObj : Object
{
public:
	ViewObj(OpenGL*);
	~ViewObj();

	void SetTexture(const char*);
	void SetTexture(GLuint);
	void Initialize(int X, int Y, int Width, int Height);
	void Shutdown();
	void Draw();
	void Reshape(int X, int Y);

	void SetExposure(double);
	void SetDensity(double);
	void SetWeight(double);
	void SetDecay(double);
	void SetPosition(float, float);

private:
	double exposure;
	double density;
	double weight;
	double cay;
	Vector2f vPosition;

	ShaderManager* m_Shader;
	Texture* m_Texture;
	OpenGL* m_OpenGL;

	vector<Vector3f> vVertex;
	vector<Vector2f> vUV;

	GLuint VertexArrayObject;
	GLuint VertexBuffer;
	GLuint UVBuffer;

	GLuint TextureID;

private:
	void Bind();
	void Build(float X, float Y, float Width, float Height);

};

#endif