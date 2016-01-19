#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <map>
#include <vector>

#include "OpenGL.h"
#include "Math3D.h"
#include "Texture.h"
#include "Model.h"
#include "ModelOBJ.h"

using std::vector;
using Math::Vector2f;
using Math::Vector3f;

class Object3D
{
public:
	Object3D(OpenGL*);
	~Object3D();

	void SetColorTexture(const char* sTexture);
	void SetHeightTexture(const char* sTexture);
	void SetNormalTexture(const char* sTexture);

	GLuint GetColorTexture();
	GLuint GetHeightTexture();
	GLuint GetNormalTexture();

	vector<Vector3f>* GetVertex();
	vector<Vector2f>* GetUV();
	vector<Vector3f>* GetNormal();

	void SetPosition(Vector3f);
	void SetRotate(Vector3f);
	void SetScale(Vector3f);

	Vector3f GetPosition();
	Vector3f GetRotate();
	Vector3f GetScale();

	Matrix44f GetWorldMatrix();

	void Initialize(const char*, const char*);
	void Initialize(const char*);
	void Initialize(vector<Vector3f>*, vector<Vector2f>*, vector<Vector3f>*);

	void Draw();
	void DrawTess();
	void Shutdown();

	void ShowWireframe(bool);
	
private:
	void SetModel(const char*);
	void Bind();
	void BuildWorldMatrix();
	void Calculate();
	
private:
	OpenGL* m_OpenGL;

private:
	map<string, Model*> mModel;

	vector<Vector3f> vVertex;
	vector<Vector3f> vNormal;
	vector<Vector3f> vBitangent;
	vector<Vector3f> vTangent;
	vector<Vector2f> vUV;

	GLuint iVAO;
	GLuint iVertexBuffer;
	GLuint iNormalBuffer;
	GLuint iUVBuffer;
	GLuint iTangentBuffer;
	GLuint iBitangentBuffer;
	
	GLuint iColorTexture;
	GLuint iNormalTexture;
	GLuint iHeightTexture;

	Matrix44f mWorldMatrix;

	Vector3f vPosition;
	Vector3f vScale;
	Vector3f vRotate;

};

#endif