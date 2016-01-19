#pragma once

#include <vector>

#include "OpenGL.h"
#include "Math3D.h"
//#include "Texture.h"
#include "Model.h"
#include "ModelOBJ.h"
#include "Shape.h"

using namespace std;
using namespace Math;

class Object : Shape
{
public:
	Object(OpenGL*);
	~Object();

	GLuint GetTexture();

	void Initialize(const char*, const char*);

	void Draw();

	void Shutdown();

private:
	vector<Vector3f> vVertex;
	vector<Vector3f> vNormal;
	vector<Vector2f> vUV;

	GLuint VertexArrayObject;
	GLuint VertexBuffer;
	GLuint NormalBuffer;
	GLuint UVBuffer;
	GLuint TexturePath;

	OpenGL* m_OpenGL;
	//Texture* m_Texture;
	Model* m_OBJ;

	void SetModel(const char*);
	void SetTexture(const char*);

	void Bind();

};