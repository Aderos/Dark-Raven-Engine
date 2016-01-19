#include "Object3D.h"

Object3D::Object3D(OpenGL* m_OpenGL) : vVertex(), vNormal(), vUV(), mModel(), vTangent(), vBitangent()
{
	this->m_OpenGL = m_OpenGL;
	this->mModel["obj"] = (Model*)new ModelOBJ;

	this->vPosition = Vector3f(0.0f);
	this->vScale    = Vector3f(1.0f);
	this->vRotate   = Vector3f(0.0f);

	this->iVAO = 0;
	this->iVertexBuffer = 0;
	this->iNormalBuffer = 0;
	this->iUVBuffer = 0;
	this->iTangentBuffer = 0;
	this->iBitangentBuffer = 0;

	this->iColorTexture = 0;
	this->iNormalTexture = 0;
	this->iHeightTexture = 0;

	this->mWorldMatrix = 0;
}

Object3D::~Object3D()
{
}

vector<Vector3f>* Object3D::GetVertex()
{
	return &vVertex;
}

vector<Vector2f>* Object3D::GetUV()
{
	return &vUV;
}

vector<Vector3f>* Object3D::GetNormal()
{
	return &vNormal;
}

void Object3D::SetColorTexture(const char* cTexture)
{
	this->iColorTexture = (new Texture(this->m_OpenGL))->GetTexture2D(cTexture);
}

void Object3D::SetNormalTexture(const char* cTexture)
{
	this->iNormalTexture = (new Texture(this->m_OpenGL))->GetTexture2D(cTexture);
}

void Object3D::SetHeightTexture(const char* cTexture)
{
	this->iHeightTexture = (new Texture(this->m_OpenGL))->GetTexture2D(cTexture);
}

GLuint Object3D::GetColorTexture()
{
	return this->iColorTexture;
}

GLuint Object3D::GetNormalTexture()
{
	return this->iNormalTexture;
}

GLuint Object3D::GetHeightTexture()
{
	return this->iHeightTexture;
}

void Object3D::SetPosition(Vector3f vPosition)
{
	this->vPosition = vPosition;
	BuildWorldMatrix();
}

Vector3f Object3D::GetPosition()
{
	return this->vPosition;
}

void Object3D::SetRotate(Vector3f vRotate)
{
	this->vRotate = vRotate;
	BuildWorldMatrix();
}

Vector3f Object3D::GetRotate()
{
	return this->vRotate;
}

void Object3D::SetScale(Vector3f vScale)
{
	this->vScale = vScale;
	BuildWorldMatrix();
}

Vector3f Object3D::GetScale()
{
	return this->vScale;
}

Matrix44f Object3D::GetWorldMatrix()
{
	return this->mWorldMatrix;
}

void Object3D::BuildWorldMatrix()
{
	Matrix44f mWorldScale = Math::Scale(this->vScale);
	Matrix44f mWorldRotate = Math::Rotate(this->vRotate);
	Matrix44f mWorldTranslation = Math::Translation(this->vPosition);

	this->mWorldMatrix = mWorldTranslation * mWorldRotate * mWorldScale;
}

void Object3D::SetModel(const char* cModelPath)
{
	int size = strlen(cModelPath);

	Model* model = 0;

	string extension{};
	extension.append(1, cModelPath[size - 3]);
	extension.append(1, cModelPath[size - 2]);
	extension.append(1, cModelPath[size - 1]);

	(model = this->mModel[extension])->Load(cModelPath, this->vVertex, this->vUV, this->vNormal);

	//Calculate();
	// ?
	//Math::computeTangentBasis(vVertex, vUV, vNormal, vTangent, vBitangent);
}

void Object3D::Initialize(vector<Vector3f>* vVertex, vector<Vector2f>* vUV, vector<Vector3f>* vNormal)
{
	this->vVertex = (*vVertex);
	this->vUV = (*vUV);
	this->vNormal = (*vNormal);
	Bind();
}

void Object3D::Initialize(const char* cModelObject, const char* cImageObject)
{
	SetModel(cModelObject);
	SetColorTexture(cImageObject);
	Bind();
}

void Object3D::Initialize(const char* cModelObject)
{
	SetModel(cModelObject);
	Bind();
}

void Object3D::Calculate()
{
	this->vTangent.clear();
	this->vBitangent.clear();

	for (unsigned int i = 0; i < vVertex.size(); i += 3)
	{
		Vector3f& v0 = vVertex[i + 0];
		Vector3f& v1 = vVertex[i + 1];
		Vector3f& v2 = vVertex[i + 2];

		Vector2f& w0 = vUV[i + 0];
		Vector2f& w1 = vUV[i + 1];
		Vector2f& w2 = vUV[i + 2];

		// Edges of the triangle : postion delta
		Vector3f deltaPos1 = v1 - v0;
		Vector3f deltaPos2 = v2 - v0;

		// UV delta
		Vector2f deltaUV1 = w1 - w0;
		Vector2f deltaUV2 = w2 - w0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;		
		Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		vTangent.push_back(tangent);
		vTangent.push_back(tangent);
		vTangent.push_back(tangent);

		vBitangent.push_back(bitangent);		
		vBitangent.push_back(bitangent);
		vBitangent.push_back(bitangent);
	}

	for (unsigned int i = 0; i < vVertex.size(); i++)
	{
		Vector3f& n = vNormal[i];
		Vector3f& t = vTangent[i];
		Vector3f& b = vBitangent[i];

		// Gram-Schmidt orthogonalize
		vTangent[i] = Normalize(t - n * Dot(n, t));

		// Calculate handedness
		if (Dot(Cross(n, t), b) < 0.0f)
		{
			vTangent[i] = t * -1.0f;
		}
	}
}

void Object3D::Bind()
{
	this->m_OpenGL->GenVertexArrays(&this->iVAO);
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->BindBufferData(this->iVertexBuffer, this->vVertex.size(), sizeof(Vector3f), &this->vVertex[0], 0, 3);
	this->m_OpenGL->BindBufferData(this->iNormalBuffer, this->vNormal.size(), sizeof(Vector3f), &this->vNormal[0], 2, 3);
	this->m_OpenGL->BindBufferData(this->iUVBuffer, this->vUV.size(), sizeof(Vector2f), &this->vUV[0], 3, 2);
	//this->m_OpenGL->BindBufferData(this->iTangentBuffer, this->vTangent.size(), sizeof(Vector3f), &this->vTangent[0], 4, 3);
	//this->m_OpenGL->BindBufferData(this->iBitangentBuffer, this->vBitangent.size(), sizeof(Vector3f), &this->vBitangent[0], 5, 3);
}

void Object3D::Draw()
{
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->DrawTriangles(0, this->vVertex.size());
}

void Object3D::DrawTess()
{
	this->m_OpenGL->BindVertexArray(&this->iVAO);
	this->m_OpenGL->DrawTess(3, 0, this->vVertex.size());
}

void Object3D::ShowWireframe(bool bWireframe)
{
	if (bWireframe)
		this->m_OpenGL->EnableWireframe();
	else
		this->m_OpenGL->DisableWireframe();
}

void Object3D::Shutdown()
{
	this->m_OpenGL->DisableVertexAttribArray(0);
	this->m_OpenGL->DisableVertexAttribArray(2);
	this->m_OpenGL->DisableVertexAttribArray(3);
	this->m_OpenGL->DisableVertexAttribArray(4);
	this->m_OpenGL->DisableVertexAttribArray(5);
	this->m_OpenGL->ReleaseVertexArray(&iVAO);
}