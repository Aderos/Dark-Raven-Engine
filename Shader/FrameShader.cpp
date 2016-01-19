#include "FrameShader.h"

FrameShader::FrameShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Frame.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Frame.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

FrameShader::~FrameShader()
{
}

void FrameShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void FrameShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);
}

void FrameShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}