#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include <vector>

#include "ShaderManager.h"
#include "OpenGL.h"
#include "Math3D.h"
#include "Object.h"
#include "Texture.h"

using std::vector;
using Math::Vector2f;
using Math::Vector3f;

class Object2D : Object
{
public:
	Object2D(OpenGL*, ShaderManager*);
	~Object2D();

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

#endif