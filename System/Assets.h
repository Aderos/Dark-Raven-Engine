#include <iostream>
#include "OpenGL.h"
#include "ShaderManager.h"
#include "Math3D.h"

using namespace Math;

class Assets
{
public:
	Assets(OpenGL*, ShaderManager*);
	~Assets();

	void SetPosition(Vector3f);
	void SetScale(Vector3f);
	void SetRotate(Vector3f);

	Vector3f GetPosition();
	Vector3f GetScale();
	Vector3f GetRotate();

	void Initialize();
	void Draw();

private:
	OpenGL* m_OpenGL;
	ShaderManager* m_Shader;

private:
	Vector3f vPosition;
	Vector3f vScale;
	Vector3f vRotate;

};