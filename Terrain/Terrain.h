#pragma once
#include <vector>

#include "OpenGL.h"
#include "ImageBMP.h"
#include "Math3D.h"
#include "ShaderManager.h"
#include "Texture.h"

using std::vector;
using namespace Math;

class Terrain
{
public:
	Terrain(OpenGL*, ShaderManager* m_Shader);
	~Terrain();

	void SetPositionLight(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetRotate(float x, float y, float z);
	void SetScale(float x, float y, float z);

	void SetPositionLight(Vector3f a);
	void SetPosition(Vector3f a);
	void SetRotate(Vector3f a);
	void SetScale(Vector3f a);
	void SetHeight(float a);

	Vector3f GetPositionLight();
	Vector3f GetPosition();
	Vector3f GetRotate();
	Vector3f GetScale();
	float GetHeight();

	void Initialize(const char* sTexture, const char* sHeightMap, const char* sNormalMap, float fHeight);
	void Draw(Matrix44f mVP, float fHeight);
	void Shutdown();

private:
	void SetHeight(int x, int z, float y);

	float GetHeight(int x, int z);
	Vector3f GetNormal(int x, int z);

	void GenerateTerrain();
	void ComputeNormal();
	void Bind();

private:
	ShaderManager* m_Shader;
	OpenGL* m_OpenGL;
	Texture* m_Texture;

	GLuint TextureID;

	Vector3f vPosition;
	Vector3f vRotate;
	Vector3f vScale;
	Vector3f vLight;

	GLuint VertexArrayObject;
	GLuint VertexBuffer;
	GLuint NormalBuffer;
	GLuint UVBuffer;

	vector<Vector3f> vVertex;
	vector<Vector3f> vNormal;
	vector<Vector2f> vUV;

	int iHeight;
	float fHeight;
	int iWidth;
	float** hs;

	Vector3f** NormalTemp;
	Vector3f** Normal;

};