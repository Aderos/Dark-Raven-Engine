#ifndef _GODRAYSSHADER_H_
#define _GODRAYSSHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "OpenGL.h"

using std::va_list;

class GodraysShader : Shader
{
public:
	GodraysShader(OpenGL* m_OpenGL);
	~GodraysShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;

	GLuint theProgram;

};

#endif