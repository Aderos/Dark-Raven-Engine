#include "ToonShader.h"

ToonShader::ToonShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/Toon.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/Toon.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

ToonShader::~ToonShader()
{
}

void ToonShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void ToonShader::SetParameters(va_list uniformList)
{
	// Set the world matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "worldMatrix", va_arg(uniformList, Matrix44f).Get());

	// Set the view matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "viewMatrix", va_arg(uniformList, Matrix44f).Get());

	// Set the projection matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "projectionMatrix", va_arg(uniformList, Matrix44f).Get());

	// Set the light dir in fragment shader.
	m_OpenGL->SetUniformVector3f(theProgram, "vLightDir", va_arg(uniformList, Vector3f).Get());

	// Set active the texture in the fragment shader.
	m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));

	// Set the texture in the fragment shader.
	m_OpenGL->SetUniform1i(theProgram, "Texture", 0);
}

void ToonShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}