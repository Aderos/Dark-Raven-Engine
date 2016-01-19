#include "CookTorranceShader.h"

CookTorranceShader::CookTorranceShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/CookTorrance.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/CookTorrance.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

CookTorranceShader::~CookTorranceShader()
{
}

void CookTorranceShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void CookTorranceShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMV", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mViewMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vLight", va_arg(uniformList, Vector3f).GetValue());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vEye", va_arg(uniformList, Vector3f).GetValue());
	this->m_OpenGL->SetUniformVector4f(this->theProgram, "vAmbient", va_arg(uniformList, Vector4f).GetValue());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vSpecular", va_arg(uniformList, Vector3f).GetValue());

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);
}

void CookTorranceShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}