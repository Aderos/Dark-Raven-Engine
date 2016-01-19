#ifndef _SHADOWMAPPINGSHADER_H_
#define _SHADOWMAPPINGSHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "Math3D.h"
#include "OpenGL.h"

using std::va_list;
using Math::Vector4f;
using Math::Matrix44f;

class ShadowMappingShader : Shader
{
public:
	ShadowMappingShader(OpenGL*);
	~ShadowMappingShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;

	GLuint theProgram;

};

#endif