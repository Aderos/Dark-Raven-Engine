#ifndef _OBJECT2DSHADER_H_
#define _OBJECT2DSHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "OpenGL.h"

using std::va_list;

class Object2DShader : Shader
{
public:
	Object2DShader(OpenGL* m_OpenGL);
	~Object2DShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;
	
	GLuint theProgram;

};

#endif