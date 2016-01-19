//#include "Object2D.h"
//
//Object2D::Object2D(OpenGL* m_OpenGL) : vVertex(), vUV()
//{
//	this->m_OpenGL = m_OpenGL;
//	this->m_Shader = new ShaderManager(m_OpenGL);
//	this->m_Texture = new Texture(m_OpenGL);
//}
//
//Object2D::~Object2D()
//{
//}
//
//void Object2D::SetTexture(const char* strImagePath)
//{
//	this->TextureID = m_Texture->GetTexture2D(strImagePath);
//}
//
//void Object2D::Initialize(int X, int Y, int Width, int Height)
//{
//	this->m_Shader->Initialize();
//	Build((float)X, (float)Y, (float)Width, (float)Height);
//	Bind();
//}
//
//void Object2D::Build(float X, float Y, float Width, float Height)
//{
//	//First triangle.
//	vVertex.push_back(Vector3f(X, Height + Y, 0)); // Top left.
//	vVertex.push_back(Vector3f(Width + X, Y, 0)); // Bottom right.
//	vVertex.push_back(Vector3f(X, Y, 0)); // Bottom left.
//
//	vUV.push_back(Vector2f(0, 1));
//	vUV.push_back(Vector2f(1, 0));
//	vUV.push_back(Vector2f(0, 0));
//
//	// Second triangle.
//	vVertex.push_back(Vector3f(X, Height + Y, 0)); // Top left.
//	vVertex.push_back(Vector3f(Width + X, Height + Y, 0)); // Top right.
//	vVertex.push_back(Vector3f(Width + X, Y, 0)); // Bottom right.
//
//	vUV.push_back(Vector2f(0, 1));
//	vUV.push_back(Vector2f(1, 1));
//	vUV.push_back(Vector2f(1, 0));
//}
//
//void Object2D::Reshape(int X, int Y)
//{
//}
//
//void Object2D::Bind()
//{
//	m_OpenGL->GenVertexArrays(&VertexArrayObject);
//	m_OpenGL->BindVertexArray(&VertexArrayObject);
//	m_OpenGL->BindBufferData(VertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
//	m_OpenGL->BindBufferData(UVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
//}
//
//void Object2D::Shutdown()
//{
//	m_OpenGL->DisableVertexAttribArray(0);
//	m_OpenGL->DisableVertexAttribArray(3);
//	m_OpenGL->ReleaseVertexArray(&VertexArrayObject);
//}
//
//void Object2D::Draw()
//{
//	m_Shader->UseShader(GLT_OBJECT_2D_SHADER, TextureID, (int)m_OpenGL->GetScreenWidth(), (int)m_OpenGL->GetScreenHeight());
//	m_OpenGL->BindVertexArray(&VertexArrayObject);
//	m_OpenGL->DrawTriangles(0, vVertex.size());
//}