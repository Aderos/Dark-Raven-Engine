#include "DissolveShader.h"

DissolveShader::DissolveShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Dissolve.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Dissolve.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

DissolveShader::~DissolveShader()
{
}

void DissolveShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void DissolveShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector4f(this->theProgram, "vDiffuse", va_arg(uniformList, Vector4f).Get());
	this->m_OpenGL->SetUniform1f(this->theProgram, "fDissolve", (float)va_arg(uniformList, double));

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);
}

void DissolveShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}