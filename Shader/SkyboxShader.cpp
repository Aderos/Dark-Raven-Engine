#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Skybox.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Skybox.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

SkyboxShader::~SkyboxShader()
{
}

void SkyboxShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void SkyboxShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	
	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);

	double val = va_arg(uniformList, double);

	float fOp = (float)val;

	this->m_OpenGL->SetUniform1f(this->theProgram, "fOpacity", fOp);
}

void SkyboxShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}