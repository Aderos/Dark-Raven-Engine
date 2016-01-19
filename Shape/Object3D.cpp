//#include "Object3D.h"
//
//Object3D::Object3D(OpenGL* m_OpenGL) : vVertex(), vNormal(), vUV(), mModel()
//{
//	this->m_OpenGL = m_OpenGL;
//	this->mModel["obj"] = (Model*)new ModelOBJ;
//	this->m_Texture = new Texture(m_OpenGL);
//}
//
//Object3D::~Object3D()
//{
//}
//
//void Object3D::SetTexture(const char* strImagePath)
//{
//	TextureID = m_Texture->GetTexture2D(strImagePath);
//}
//
//GLuint Object3D::GetTexture()
//{
//	return this->TextureID;
//}
//
//void Object3D::SetModel(const char* strModelPath)
//{
//	int size = strlen(strModelPath);
//
//	Model* model = 0;
//
//	string extension{};
//	extension.append(1, strModelPath[size - 3]);
//	extension.append(1, strModelPath[size - 2]);
//	extension.append(1, strModelPath[size - 1]);
//
//	(model = mModel[extension])->Load(strModelPath, vVertex, vUV, vNormal);
//}
//
//void Object3D::Initialize(const char* strModelObject, const char* strImageObject)
//{
//	SetModel(strModelObject);
//	SetTexture(strImageObject);
//	Bind();
//}
//
//void Object3D::Bind()
//{
//	m_OpenGL->GenVertexArrays(&VertexArrayObject);
//	m_OpenGL->BindVertexArray(&VertexArrayObject);
//	m_OpenGL->BindBufferData(VertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
//	m_OpenGL->BindBufferData(NormalBuffer, vNormal.size(), sizeof(Vector3f), &vNormal[0], 2, 3);
//	m_OpenGL->BindBufferData(UVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
//}
//
//void Object3D::Draw()
//{
//	m_OpenGL->BindVertexArray(&VertexArrayObject);
//	m_OpenGL->DrawTriangles(0, vVertex.size());
//}
//
//void Object3D::Shutdown()
//{
//	m_OpenGL->DisableVertexAttribArray(0);
//	m_OpenGL->DisableVertexAttribArray(2);
//	m_OpenGL->DisableVertexAttribArray(3);
//	m_OpenGL->ReleaseVertexArray(&VertexArrayObject);
//}