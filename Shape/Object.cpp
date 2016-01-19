#include "Object.h"

Object::Object(OpenGL* m_OpenGL) : vVertex(), vNormal(), vUV()
{
	this->m_OpenGL = m_OpenGL;
	this->m_OBJ = (Model*)new ModelOBJ;
	//this->m_Texture = new Texture(m_OpenGL);
}

Object::~Object()
{
}

void Object::SetTexture(const char* strImagePath)
{
	//TexturePath = m_Texture->GetTexture(strImagePath);
}

GLuint Object::GetTexture()
{
	return this->TexturePath;
}

void Object::SetModel(const char* strModelPath)
{
	int size = strlen(strModelPath);

	// OBJ
	if (strModelPath[size - 3] == 'o' && strModelPath[size - 2] == 'b' && strModelPath[size - 1] == 'j')
	{
		m_OBJ->Load(strModelPath, vVertex, vUV, vNormal);
	}
}

void Object::Initialize(const char* strModelObject, const char* strImageObject)
{
	SetModel(strModelObject);
	SetTexture(strImageObject);
	Bind();
}

void Object::Bind()
{
	m_OpenGL->BindVertexArray(&VertexArrayObject);
	m_OpenGL->BindBufferData(VertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
	m_OpenGL->BindBufferData(NormalBuffer, vNormal.size(), sizeof(Vector3f), &vNormal[0], 2, 3);
	m_OpenGL->BindBufferData(UVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
}

void Object::Shutdown()
{
	m_OpenGL->glDisableVertexAttribArray(0);
	m_OpenGL->glDisableVertexAttribArray(2);
	m_OpenGL->glDisableVertexAttribArray(3);

	m_OpenGL->ReleaseVertexArray(&VertexArrayObject);

	if (m_OBJ)
	{
		delete m_OBJ;
		m_OBJ = 0;
	}

	//if (m_Texture)
	//{
	//	m_Texture->Shutdown();
	//	delete m_Texture;
	//	m_Texture = 0;
	//}
}

void Object::Draw()
{
	// Bind the vertex array object that stored all the information about the vertex and index buffers.
	m_OpenGL->glBindVertexArray(VertexArrayObject);

	// Render the vertex buffer using the index buffer.
	glDrawArrays(GL_TRIANGLES, 0, vVertex.size());
}