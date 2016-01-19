//#include "MatrixStack.h"
//
//MatrixStack::MatrixStack()
//{
//	matrix = Matrix44f(0);
//
//	translationMatrix = Math::Identity4x4();
//	rotateMatrix = Math::Identity4x4();
//	scaleMatrix = Math::Identity4x4();
//}
//
//MatrixStack::~MatrixStack()
//{
//}
//
//void MatrixStack::Rotate(Vector3f Rotate)
//{
//	rotateMatrix = Math::Rotate(Rotate);
//}
//
//void MatrixStack::Rotate(float x, float y, float z)
//{
//	Rotate(Vector3f(x, y, z));
//}
//
//void MatrixStack::Scale(Vector3f Scale)
//{
//	scaleMatrix = Math::Scale(Scale);
//}
//
//void MatrixStack::Scale(float x, float y, float z)
//{
//	Scale(Vector3f(x, y, z));
//}
//
//void MatrixStack::Translate(Vector3f Translate)
//{
//	translationMatrix = Math::Translation(Translate);
//}
//
//void MatrixStack::Translate(float x, float y, float z)
//{
//	Translate(Vector3f(x, y, z));
//}
//
//void MatrixStack::Push(Matrix44f matrix)
//{
//	if (this->matrix == Matrix44f(0)) { this->matrix = matrix; }
//	else { this->matrix = this->matrix * matrix; }
//}
//
//Matrix44f MatrixStack::Pop()
//{
//	return translationMatrix * rotateMatrix * scaleMatrix * matrix;
//}