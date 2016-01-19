#include "Terrain.h"

Terrain::Terrain(OpenGL* m_OpenGL, ShaderManager* m_Shader)
{
	this->m_OpenGL = m_OpenGL;
	this->m_Shader = m_Shader;
}

Terrain::~Terrain()
{
}

void Terrain::SetPosition(Vector3f vPosition)
{
	this->vPosition = vPosition;
}

void Terrain::SetPosition(float x, float y, float z)
{
	SetPosition(Vector3f(x, y, z));
}

void Terrain::SetRotate(Vector3f vRotate)
{
	this->vRotate = vRotate;
}

void Terrain::SetRotate(float x, float y, float z)
{
	SetRotate(Vector3f(x, y, z));
}

void Terrain::SetScale(Vector3f vScale)
{
	this->vScale = vScale;
}

void Terrain::SetScale(float x, float y, float z)
{
	SetScale(Vector3f(x, y, z));
}

void Terrain::SetPositionLight(Vector3f vLight)
{
	this->vLight = vLight;
}

void Terrain::SetPositionLight(float x, float y, float z)
{
	SetPositionLight(Vector3f(x, y, z));
}

void Terrain::SetHeight(float a)
{
	this->fHeight = a;
}

float Terrain::GetHeight()
{
	return this->fHeight;
}

Vector3f Terrain::GetPosition()
{
	return this->vPosition;
}

Vector3f Terrain::GetRotate()
{
	return this->vRotate;
}

Vector3f Terrain::GetScale()
{
	return this->vScale;
}

Vector3f Terrain::GetPositionLight()
{
	return this->vLight;
}

void Terrain::SetHeight(int x, int z, float y)
{
	hs[z][x] = y;
}

float Terrain::GetHeight(int x, int z)
{
	return hs[z][x];
}

Vector3f Terrain::GetNormal(int x, int z)
{
	return Normal[z][x];
}

void Terrain::Initialize(const char* sTexture, const char* sHeightMap, const char* sNormalMap, float fHeight)
{
	SetHeight(fHeight);

	ImageBMP* image = new ImageBMP(m_OpenGL);
	image->Load(sHeightMap);

	m_Texture = new Texture(m_OpenGL);
	TextureID = m_Texture->GetTexture2D(sTexture);

	iWidth = image->GetWidth();
	iHeight = image->GetHeight();

	hs = new float*[image->GetHeight()];
	Normal = new Vector3f*[image->GetHeight()];
	NormalTemp = new Vector3f*[image->GetHeight()];

	for (unsigned int i = 0; i < image->GetHeight(); ++i)
	{
		hs[i] = new float[image->GetWidth()];
		Normal[i] = new Vector3f[image->GetWidth()];
		NormalTemp[i] = new Vector3f[image->GetWidth()];
	}

	for (unsigned int y = 0; y < image->GetHeight(); y++)
	{
		for (unsigned int x = 0; x < image->GetWidth(); x++)
		{
			unsigned char color = (unsigned char)image->GetData()[3 * (y * image->GetWidth() + x)];
			float h = ((color / 255.0f) - 0.5f);
			SetHeight(x, y, h);
		}
	}

	ComputeNormal();
	GenerateTerrain();
	Bind();

	vPosition = Vector3f(0, -20, 0);
}

void Terrain::ComputeNormal()
{
	for (int z = 0; z < iHeight; z++)
	{
		for (int x = 0; x < iWidth; x++)
		{
			Vector3f sum(0.0f, 0.0f, 0.0f);

			Vector3f out;
			if (z > 0) { out = Vector3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f); }

			Vector3f in;
			if (z < iHeight - 1) { in = Vector3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f); }

			Vector3f left;
			if (x > 0) { left = Vector3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f); }

			Vector3f right;
			if (x < iWidth - 1) { right = Vector3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f); }

			if (x > 0 && z > 0)
			{
				sum += Normalize(Cross(out, left));
			}
			if (x > 0 && z < iHeight - 1)
			{
				sum += Normalize(Cross(left, in));
			}
			if (x < iWidth - 1 && z < iHeight - 1)
			{
				sum += Normalize(Cross(in, right));
			}
			if (x < iWidth - 1 && z > 0)
			{
				sum += Normalize(Cross(right, out));
			}

			NormalTemp[z][x] = sum;
		}
	}

	const float FALLOUT_RATIO = 0.5f;
	for (int z = 0; z < iHeight; z++)
	{
		for (int x = 0; x < iWidth; x++)
		{
			Vector3f sum = NormalTemp[z][x];

			if (x > 0) { sum += NormalTemp[z][x - 1] * FALLOUT_RATIO; }

			if (x < iWidth - 1) { sum += NormalTemp[z][x + 1] * FALLOUT_RATIO; }

			if (z > 0) { sum += NormalTemp[z - 1][x] * FALLOUT_RATIO; }

			if (z < 0) { sum += NormalTemp[z + 1][x]; }

			Normal[z][x] = sum;
		}
	}
}

void Terrain::GenerateTerrain()
{
	for (int z = 0; z < iHeight - 1; z++)
	{
		for (int x = 0; x < iWidth - 1; x++)
		{
			float fX = (float)x / (float)iWidth;
			float fZ = (float)z / (float)iHeight;

			float fX1 = (float)(x + 1) / (float)iWidth;
			float fZ1 = (float)(z + 1) / (float)iHeight;

			float fPosX = x - ((float)iWidth / 2);
			float fPosZ = z - ((float)iHeight / 2);

			vVertex.push_back(Vector3f(fPosX, GetHeight(x, z), fPosZ));
			vNormal.push_back(GetNormal(x, z));
			vUV.push_back(Vector2f(fX, fZ));

			vVertex.push_back(Vector3f(fPosX, GetHeight(x, z + 1), fPosZ + 1));
			vNormal.push_back(GetNormal(x, z + 1));
			vUV.push_back(Vector2f(fX, fZ1));

			vVertex.push_back(Vector3f(fPosX + 1, GetHeight(x + 1, z), fPosZ));
			vNormal.push_back(GetNormal(x + 1, z));
			vUV.push_back(Vector2f(fX1, fZ));

			vVertex.push_back(Vector3f(fPosX + 1, GetHeight(x + 1, z), fPosZ));
			vNormal.push_back(GetNormal(x + 1, z));
			vUV.push_back(Vector2f(fX1, fZ));

			vVertex.push_back(Vector3f(fPosX, GetHeight(x, z + 1), fPosZ + 1));
			vNormal.push_back(GetNormal(x, z + 1));
			vUV.push_back(Vector2f(fX, fZ1));

			vVertex.push_back(Vector3f(fPosX + 1, GetHeight(x + 1, z + 1), fPosZ + 1));
			vNormal.push_back(GetNormal(x + 1, z + 1));
			vUV.push_back(Vector2f(fX1, fZ1));
		}
	}
}

void Terrain::Bind()
{
	m_OpenGL->BindVertexArray(&VertexArrayObject);
	m_OpenGL->BindBufferData(VertexBuffer, vVertex.size(), sizeof(Vector3f), &vVertex[0], 0, 3);
	m_OpenGL->BindBufferData(NormalBuffer, vNormal.size(), sizeof(Vector3f), &vNormal[0], 2, 3);
	m_OpenGL->BindBufferData(UVBuffer, vUV.size(), sizeof(Vector2f), &vUV[0], 3, 2);
}

void Terrain::Draw(Matrix44f mVP, float fHeight)
{
	Matrix44f mWorldScale = Math::Scale(vScale);
	Matrix44f mWorldRotate = Math::Rotate(vRotate);
	Matrix44f mWorldTranslation = Math::Translation(vPosition);

	Matrix44f mWorldMatrix = mWorldTranslation * mWorldRotate * mWorldScale;

	m_Shader->UseShader(GLT_TERRAIN_SHADER, mVP * mWorldMatrix, (double)fHeight, TextureID);

	m_OpenGL->BindVertexArray(&VertexArrayObject);
	m_OpenGL->DrawTriangles(0, vVertex.size());

	m_Shader->Reset();
}

void Terrain::Shutdown()
{
	m_OpenGL->DisableVertexAttribArray(0);
	m_OpenGL->ReleaseVertexArray(&VertexArrayObject);
}