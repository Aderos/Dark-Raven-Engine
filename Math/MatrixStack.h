//#pragma once
//
//#include "Math3D.h"
//
//using namespace Math;
//
//class MatrixStack
//{
//public:
//	MatrixStack();
//	~MatrixStack();
//
//	void Rotate(Vector3f);
//	void Rotate(float x, float y, float z);
//
//	void Scale(Vector3f);
//	void Scale(float x, float y, float z);
//
//	void Translate(Vector3f);
//	void Translate(float x, float y, float z);
//	
//	void Push(Matrix44f matrix);
//	Matrix44f Pop();
//
//private:
//	Matrix44f matrix;
//
//	Matrix44f translationMatrix;
//	Matrix44f rotateMatrix;
//	Matrix44f scaleMatrix;
//
//};