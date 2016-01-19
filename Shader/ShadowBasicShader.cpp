#include "ShadowBasicShader.h"

ShadowBasicShader::ShadowBasicShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/ShadowBasic.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/ShadowBasic.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

ShadowBasicShader::~ShadowBasicShader()
{
}

void ShadowBasicShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void ShadowBasicShader::SetParameters(va_list uniformList)
{
	m_OpenGL->BindActiveShadowTexture2D(va_arg(uniformList, GLuint));
	m_OpenGL->SetUniform1i(theProgram, "iTexture", 1);
}

void ShadowBasicShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}