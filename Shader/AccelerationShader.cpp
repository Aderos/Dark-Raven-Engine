#include "AccelerationShader.h"

AccelerationShader::AccelerationShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetComputeShader(), "../Shader/Acceleration.co"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

AccelerationShader::~AccelerationShader()
{
}

void AccelerationShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void AccelerationShader::SetParameters(va_list uniformList)
{
	m_OpenGL->glDispatchCompute(va_arg(uniformList, int), 1, 1);
	m_OpenGL->glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void AccelerationShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}