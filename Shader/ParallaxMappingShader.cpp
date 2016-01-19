#include "ParallaxMappingShader.h"

ParallaxMappingShader::ParallaxMappingShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/ParallaxMapping.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/ParallaxMapping.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

ParallaxMappingShader::~ParallaxMappingShader()
{
}

void ParallaxMappingShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void ParallaxMappingShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMV", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mViewMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vLightPos", va_arg(uniformList, Vector3f).GetValue());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vEyePos", va_arg(uniformList, Vector3f).GetValue());
	this->m_OpenGL->SetUniformVector4f(this->theProgram, "vAmbient", va_arg(uniformList, Vector4f).GetValue());

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iDiffuseTexture", 0);

	this->m_OpenGL->BindActiveNormalTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iNormalTexture", 1);

	this->m_OpenGL->BindActiveHeightTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iHeightTexture", 2);

	float fParallaxScale = (float)va_arg(uniformList, int) / 100;
	this->m_OpenGL->SetUniform1f(this->theProgram, "fparallaxScale", fParallaxScale);
}

void ParallaxMappingShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}