#ifndef _PARALLAXMAPPINGSHADER_H_
#define _PARALLAXMAPPINGSHADER_H_

#include <vector>

#include "ShaderCompiler.h"
#include "Shader.h"
#include "Math3D.h"
#include "OpenGL.h"

using std::va_list;
using Math::Vector4f;
using Math::Matrix44f;

class ParallaxMappingShader : Shader
{
public:
	ParallaxMappingShader(OpenGL*);
	~ParallaxMappingShader();

	void Shutdown();
	void SetShader();
	void SetParameters(va_list);

private:
	ShaderCompiler* m_ShaderCompiler;
	OpenGL* m_OpenGL;

	GLuint theProgram;

};

#endif