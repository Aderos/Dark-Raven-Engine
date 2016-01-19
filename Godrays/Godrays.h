#ifndef _GODRAYS_H_
#define _GODRAYS_H_

#include <vector>

#include "ShaderManager.h"
#include "Object3D.h"
#include "OpenGL.h"
#include "Math3D.h"

using Math::Matrix44f;
using Math::Vector2f;
using Math::Vector3f;
using std::vector;

class Godrays
{
public:
	Godrays(OpenGL*, ShaderManager* m_Shader);
	~Godrays();

	void Initialize(int, int);
	
	void SetPosition(Vector3f);
	void SetRotate(Vector3f);
	void SetScale(Vector3f);

	Vector3f GetPosition();
	Vector3f GetRotate();
	Vector3f GetScale();

	void SetTexture(GLuint);
	void SetColor(Vector3f);
	
	void SetExposure(double);
	void SetDensity(double);
	void SetWeight(double);
	void SetDecay(double);

	double GetExposure();
	double GetDensity();
	double GetWeight();
	double GetDecay();
	
	Vector3f GetColor();
	
	void DrawSun(Matrix44f);
	void DrawGod(Matrix44f, Vector3f vPos);

	void Shutdown();

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;
	Object3D* m_Sun;
	
private:
	double dExposure;
	double dDensity;
	double dWeight;
	double dDecay;
	
	Vector3f vColor;

	vector<Vector3f> vVertex;
	vector<Vector2f> vUV;

	GLuint iVAO;
	GLuint iVertexBuffer;
	GLuint iUVBuffer;
	GLuint iTexture;
	
private:
	void Bind();
	void Build(float, float);

};

#endif