#ifndef _PIVOT_H_
#define _PIVOT_H_

#include <vector>

#include "OpenGL.h"
#include "Math3D.h"
#include "Object3D.h"
#include "ShaderManager.h"

using std::vector;
using Math::Vector3f;

class Pivot
{
public:
	Pivot(OpenGL*, ShaderManager*);
	~Pivot();

	void SetScale(Vector3f);
	void SetPosition(Vector3f);
	void SetRotate(Vector3f);

	Vector3f GetScale();
	Vector3f GetPosition();
	Vector3f GetRotate();

	Matrix44f GetWorldMatrix();

	void Initialize();
	void Draw(Matrix44f mVP);
	void Shutdown();

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;
	Object3D* m_Obj[1];

};

#endif