#ifndef _LAMBERT_TEXTURE_SHADER_H_
#define _LAMBERT_TEXTURE_SHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "Math3D.h"
#include "OpenGL.h"

using std::va_list;
using Math::Vector4f;
using Math::Matrix44f;

class LambertTextureShader : Shader
{
public:
	LambertTextureShader(OpenGL*);
	~LambertTextureShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;

	GLuint theProgram;

};

#endif