//#ifndef _OBJECT2D_H_
//#define _OBJECT2D_H_
//
//#include <vector>
//
//#include "ShaderManager.h"
//#include "OpenGL.h"
//#include "Math3D.h"
//#include "Shape.h"
//#include "Texture.h"
//
//using std::vector;
//using Math::Vector2f;
//using Math::Vector3f;
//
//class Object2D : Shape
//{
//public:
//	Object2D(OpenGL*);
//	~Object2D();
//
//	void SetTexture(const char*);
//	void Initialize(int X, int Y, int Width, int Height);
//	void Shutdown();
//	void Draw();
//	void Reshape(int X, int Y);
//
//private:
//	ShaderManager* m_Shader;
//	Texture* m_Texture;
//	OpenGL* m_OpenGL;
//
//	vector<Vector3f> vVertex;
//	vector<Vector2f> vUV;
//
//	GLuint VertexArrayObject;
//	GLuint VertexBuffer;
//	GLuint UVBuffer;
//
//	GLuint TextureID;
//
//private:
//	void Bind();
//	void Build(float X, float Y, float Width, float Height);
//
//};
//
//#endif