#ifndef _SKYBOXSHADER_H_
#define _SKYBOXSHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "OpenGL.h"

using std::va_list;
using Math::Vector4f;
using Math::Matrix44f;

class SkyboxShader : Shader
{
public:
	SkyboxShader(OpenGL* m_OpenGL);
	~SkyboxShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;

	GLuint theProgram;

};

#endif