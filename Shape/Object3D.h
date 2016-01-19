//#ifndef _OBJECT3D_H_
//#define _OBJECT3D_H_
//
//#include <map>
//#include <vector>
//
//#include "OpenGL.h"
//#include "Math3D.h"
//#include "Texture.h"
//#include "Model.h"
//#include "ModelOBJ.h"
//
//using std::vector;
//using Math::Vector2f;
//using Math::Vector3f;
//
//class Object3D
//{
//public:
//	Object3D(OpenGL*);
//	~Object3D();
//
//	GLuint GetTexture();
//
//	void Initialize(const char*, const char*);
//	void Draw();
//	void Shutdown();
//
//private:
//	void SetModel(const char*);
//	void SetTexture(const char*);
//	void Bind();
//
//private:
//	OpenGL* m_OpenGL;
//	Texture* m_Texture;
//
//	map<string, Model*> mModel;
//
//	vector<Vector3f> vVertex;
//	vector<Vector3f> vNormal;
//	vector<Vector2f> vUV;
//
//	GLuint VertexArrayObject;
//	GLuint VertexBuffer;
//	GLuint NormalBuffer;
//	GLuint UVBuffer;
//	GLuint TextureID;
//
//};
//
//#endif