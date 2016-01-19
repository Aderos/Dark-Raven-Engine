#ifndef _GRID_H_
#define _GRID_H_

#include <vector>

#include "ShaderManager.h"
#include "OpenGL.h"
#include "Math3D.h"

using Math::Vector3f;
using std::vector;

class Grid
{
public:
	Grid(OpenGL*, ShaderManager*);
	~Grid();

	void SetPosition(Vector3f);
	void SetRotate(Vector3f);
	void SetScale(Vector3f);

	Vector3f GetPosition();
	Vector3f GetRotate();
	Vector3f GetScale();

	Matrix44f GetWorldMatrix();

	void Initialize();
	void Draw(Matrix44f mVP);
	void Shutdown();

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;
	
private:
	vector<Vector3f> vVertex;
	
	GLuint iVAO;
	GLuint iVertexBuffer;
	
	Matrix44f mWorldMatrix;

	Vector3f vPosition;
	Vector3f vScale;
	Vector3f vRotate;

private:
	void Bind();
	void BuildWorldMatrix();

};

#endif