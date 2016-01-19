#ifndef _SHADERCOMPILER_H_
#define _SHADERCOMPILER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "OpenGL.h"

using std::vector;
using std::cout;
using std::endl;
using std::ifstream;

class ShaderCompiler
{
public:
	ShaderCompiler(OpenGL*);

	GLuint LoadShader(GLenum, char*);
	GLuint CreateProgram(std::vector<GLuint> ShaderList);

	void Shutdown();

private:
	OpenGL* m_OpenGL;

private:
	vector<GLuint> vShaderList;
	GLuint uiShaderProgram;

private:
	char* LoadShaderSourceFile(char*);
	bool OutputLinkerErrorMessage(unsigned int);
	bool OutputShaderErrorMessage(unsigned int);

};

#endif