#include "Object2DShader.h"

Object2DShader::Object2DShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/Object2D.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/Object2D.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

Object2DShader::~Object2DShader()
{
}

void Object2DShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void Object2DShader::SetParameters(va_list uniformList)
{
	// Set active the texture in the fragment shader.
	m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));

	// Set the texture in the fragment shader.
	m_OpenGL->SetUniform1i(theProgram, "Texture", 0);

	// Set the width in the vertex shader.
	m_OpenGL->SetUniform1i(theProgram, "iWidth", va_arg(uniformList, int));

	// Set the height in the vertex shader.
	m_OpenGL->SetUniform1i(theProgram, "iHeight", va_arg(uniformList, int));
}

void Object2DShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}