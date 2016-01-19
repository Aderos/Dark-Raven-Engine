#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "Math3D.h"
#include "OpenGL.h"

using Math::Vector3f;
using Math::Matrix44f;

class Pipeline
{
public:
	Pipeline(OpenGL*);
	~Pipeline();

	Matrix44f GetProjectionMatrix();
	Matrix44f GetOrthographicMatrix();
	Matrix44f GetCameraMatrix();
	Matrix44f GetViewProjectionMatrix();
	Matrix44f GetViewOrthographicMatrix();

	void SetCameraPosition(Vector3f a);
	Vector3f GetCameraPosition();

	void SetCameraAngleX(float);
	void SetCameraAngleY(float);

	float GetCameraAngleX();
	float GetCameraAngleY();

	void CameraKeyboard(unsigned int, int, int);
	
	void UpdateProjection();
	void UpdateOrthographic();
	void UpdateCamera();

	void Initialize(float fFOV, float fNear, float fFar);

	void SetCameraLookAt(Vector3f, Vector3f, Vector3f);
	Matrix44f GetCameraLookAt();

	Matrix44f GetProjLookAt();
	Matrix44f GetOrthLookAt();

private:
	OpenGL* m_OpenGL;

private:
	Vector3f vPosition;

	Matrix44f mCamera;
	Matrix44f mCameraLookAt;
	Matrix44f mProjection;
	Matrix44f mOrthographic;
	Matrix44f mVP;
	Matrix44f mVO;

	int iMouseX;
	int iMouseY;

	float fFOV;
	float fNear;
	float fFar;

	float fAngleY;
	float fAngleX;

private:
	void BuildCameraMatrix();
	void BuildProjectionMatrix();
	void BuildOrthographicMatrix();
	void BuildViewProjection();
	void BuildViewOrthographic();

};

#endif