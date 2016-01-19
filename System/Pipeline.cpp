#include "Pipeline.h"

Pipeline::Pipeline(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;

	this->vPosition = Vector3f(0.0f, 0.0f, -3.0f);
	this->iMouseX = 0;
	this->iMouseY = 0;
	this->fFOV = 45.0f;
	this->fNear = 1.0f;
	this->fFar = 100.f;
	this->fAngleY = 0.0f;
	this->fAngleX = 0.0f;

	this->mVP = 0;
	this->mVO = 0;
}

Pipeline::~Pipeline()
{
}

void Pipeline::CameraKeyboard(unsigned int key, int x, int y)
{
	// z
	if (key == 122)
	{
		SetCameraPosition(Vector3f(vPosition.x, vPosition.y, vPosition.z+1));
	}
	// x
	else if (key == 120)
	{
		SetCameraPosition(Vector3f(vPosition.x, vPosition.y, vPosition.z-1));
	}
}

void Pipeline::SetCameraPosition(Vector3f vPosition)
{
	this->vPosition = vPosition;
	UpdateCamera();
}

void Pipeline::SetCameraAngleX(float fAngleX)
{
	this->fAngleX = fAngleX;
	UpdateCamera();
}

void Pipeline::SetCameraAngleY(float fAngleY)
{
	this->fAngleY = fAngleY;
	UpdateCamera();
}

Vector3f Pipeline::GetCameraPosition()
{
	return this->vPosition;
}

float Pipeline::GetCameraAngleX()
{
	return this->fAngleX;
}

float Pipeline::GetCameraAngleY()
{
	return this->fAngleY;
}

Matrix44f Pipeline::GetCameraMatrix()
{
	return this->mCamera;
}

Matrix44f Pipeline::GetProjectionMatrix()
{
	return this->mProjection;
}

Matrix44f Pipeline::GetOrthographicMatrix()
{
	return this->mOrthographic;
}

Matrix44f Pipeline::GetViewProjectionMatrix()
{
	return this->mVP;
}

void Pipeline::Initialize(float fFOV, float fNear, float fFar)
{
	this->fFOV = fFOV;
	this->fNear = fNear;
	this->fFar = fFar;

	BuildProjectionMatrix();
	BuildOrthographicMatrix();
	BuildCameraMatrix();
	BuildViewProjection();
	BuildViewOrthographic();
}

void Pipeline::UpdateCamera()
{
	BuildCameraMatrix();
	BuildViewProjection();
	BuildViewOrthographic();
}

void Pipeline::UpdateOrthographic()
{
	BuildOrthographicMatrix();
	BuildViewOrthographic();
}

void Pipeline::UpdateProjection()
{
	BuildProjectionMatrix();
	BuildViewProjection();
}

void Pipeline::SetCameraLookAt(Vector3f vPosition, Vector3f vTarget, Vector3f vUp)
{
	Matrix44f mCameraTra, mCameraRot;
	
	mCameraTra = Matrix44f(
		1, 0, 0, vPosition.x,
		0, 1, 0, vPosition.y,
		0, 0, 1, vPosition.z,
		0, 0, 0, 1);

	Vector3f N = Math::Normalize(vTarget);
	Vector3f U = Math::Normalize(vUp);
	U = Math::Cross(U, N);
	Vector3f V = Math::Cross(N, U);

	mCameraRot[0]  = U.x;   mCameraRot[1]  = U.y;   mCameraRot[2]  = U.z;   mCameraRot[3]  = 0.0f;
	mCameraRot[4]  = V.x;   mCameraRot[5]  = V.y;   mCameraRot[6]  = V.z;   mCameraRot[7]  = 0.0f;
	mCameraRot[8]  = N.x;   mCameraRot[9]  = N.y;   mCameraRot[10] = N.z;   mCameraRot[11] = 0.0f;
	mCameraRot[12] = 0.0f;  mCameraRot[13] = 0.0f;  mCameraRot[14] = 0.0f;  mCameraRot[15] = 1.0f;

	//mCameraLookAt = mCameraTra;

	//Math::Identity(mCameraTra);
	//Math::Translation(mCameraTra, -vPosition);
	//mCameraRot = Math::CameraTranslation(vTarget, vUp);

	//mCameraLookAt = Math::Transpose(mCameraRot) * mCameraTra;

	mCameraLookAt = mCameraRot * mCameraTra;
}

Matrix44f Pipeline::GetProjLookAt()
{
	const float ar = m_OpenGL->GetScreenWidth() / m_OpenGL->GetScreenHeight();
	const float zNear = fNear;
	const float zFar = fFar;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(ToRadian(fFOV / 2.0));

	Matrix44f m;

	m[0] = 1.0f / (tanHalfFOV * ar);
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = 0.0f;

	m[4] = 0.0f;
	m[5] = 1.0f / tanHalfFOV;
	m[6] = 0.0f;
	m[7] = 0.0f;

	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = (-zNear - zFar) / zRange;
	m[11] = 2.0f * zFar * zNear / zRange;

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 1.0f;
	m[15] = 0.0f;

	return m;
}

Matrix44f Pipeline::GetOrthLookAt()
{
	Matrix44f m;

	const float zRange = fFar - fNear;

	m[0] = 2.0f / m_OpenGL->GetScreenWidth(); m[1] = 0.0f;          m[2] = 0.0f;        m[3] = 0.0;
	m[4] = 0.0f;         m[5] = 2.0f / m_OpenGL->GetScreenHeight(); m[6] = 0.0f;        m[7] = 0.0;
	m[8] = 0.0f;         m[9] = 0.0f;          m[10] = 2.0f / zRange; m[11] = (-fFar - fNear) / zRange;
	m[12] = 0.0f;         m[13] = 0.0f;          m[14] = 0.0f;        m[15] = 1.0;

	return m;
}

Matrix44f Pipeline::GetCameraLookAt()
{
	return this->mCameraLookAt;
}

void Pipeline::BuildProjectionMatrix()
{
	float height = fNear * tanf(Math::DegToRad(fFOV / 2));
	float width = height * m_OpenGL->GetScreenWidth() / m_OpenGL->GetScreenHeight();

	Math::Identity(mProjection);

	this->mProjection[0]  = fNear / width;
	this->mProjection[5] = fNear / height;
	this->mProjection[10] = -(fFar + fNear) / (fFar - fNear);
	this->mProjection[11] = -(2 * fFar * fNear) / (fFar - fNear);
	this->mProjection[14] = -1.0f;
	this->mProjection[15] = 0.0f;
}

void Pipeline::BuildOrthographicMatrix()
{
	float height = fNear * tanf(Math::DegToRad(fFOV / 2));
	float width = height * m_OpenGL->GetScreenWidth() / m_OpenGL->GetScreenHeight();

	Math::Identity(mOrthographic);

	this->mOrthographic[0] = 1 / width;
	this->mOrthographic[5] = 1 / height;
	this->mOrthographic[10] = -2 / (fFar - fNear);
	this->mOrthographic[11] = -(fFar + fNear) / (fFar - fNear);
}

void Pipeline::BuildCameraMatrix()
{
	Math::Identity(mCamera);
	Math::Rotate(mCamera, fAngleY / 10, 0, 1, 0);
	Math::Rotate(mCamera, fAngleX / 10, 1, 0, 0);
	Math::Translation(mCamera, vPosition);
}

void Pipeline::BuildViewProjection()
{
	this->mVP = GetProjectionMatrix() * GetCameraMatrix();
}

void Pipeline::BuildViewOrthographic()
{
	this->mVO = GetOrthographicMatrix() * GetCameraMatrix();
}