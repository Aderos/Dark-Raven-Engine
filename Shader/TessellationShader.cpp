#include "TessellationShader.h"

TessellationShader::TessellationShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Tessellation.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetTessControlShader(), "../Shader/Tessellation.cons"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetTessEvaluationShader(), "../Shader/Tessellation.evas"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Tessellation.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

TessellationShader::~TessellationShader()
{
}

void TessellationShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void TessellationShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vEyePos", va_arg(uniformList, Vector3f).GetValue());

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);

	this->m_OpenGL->BindActiveHeightTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iDisplacementMap", 2);

	this->m_OpenGL->SetUniform1f(this->theProgram, "fDispFactor", (float)va_arg(uniformList, int) / 100);
}

void TessellationShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}