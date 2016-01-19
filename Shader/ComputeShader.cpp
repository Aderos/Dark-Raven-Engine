#include "ComputeShader.h"

ComputeShader::ComputeShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetComputeShader(), "../Shader/Compute.co"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

ComputeShader::~ComputeShader()
{
}

void ComputeShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void ComputeShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniform1f(this->theProgram, "fRoll", (float)va_arg(uniformList, int) * 0.01f);

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);

	m_OpenGL->glDispatchCompute(512 / 16, 512 / 16, 1);
}

void ComputeShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}