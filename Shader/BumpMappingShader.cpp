#include "BumpMappingShader.h"

BumpMappingShader::BumpMappingShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/BumpMapping.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/BumpMapping.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

BumpMappingShader::~BumpMappingShader()
{
}

void BumpMappingShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void BumpMappingShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vLight", va_arg(uniformList, Vector3f).GetValue());
	this->m_OpenGL->SetUniformVector4f(this->theProgram, "vAmbient", va_arg(uniformList, Vector4f).GetValue());

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);

	this->m_OpenGL->BindActiveNormalTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iNormalTexture", 1);
}

void BumpMappingShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}