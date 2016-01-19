#include "ParticleShader.h"

ParticleShader::ParticleShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Particle.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Particle.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

ParticleShader::~ParticleShader()
{
}

void ParticleShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void ParticleShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mVP", va_arg(uniformList, Matrix44f).GetTranspose());
}

void ParticleShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}