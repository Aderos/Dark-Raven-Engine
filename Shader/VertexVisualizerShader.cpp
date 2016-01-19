#include "VertexVisualizerShader.h"

VertexVisualizerShader::VertexVisualizerShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/VertexVisualizer.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/VertexVisualizer.ps"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetGeometryShader(), "../Shader/VertexVisualizer.gs"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

VertexVisualizerShader::~VertexVisualizerShader()
{
}

void VertexVisualizerShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void VertexVisualizerShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniform1i(this->theProgram, "bNormal", va_arg(uniformList, int));
	this->m_OpenGL->SetUniform1f(this->theProgram, "fNormal", (float)va_arg(uniformList, double));
	this->m_OpenGL->SetUniform1i(this->theProgram, "bTangent", va_arg(uniformList, int));
	this->m_OpenGL->SetUniform1f(this->theProgram, "fTangent", (float)va_arg(uniformList, double));
	this->m_OpenGL->SetUniform1i(this->theProgram, "bBitangent", va_arg(uniformList, int));
	this->m_OpenGL->SetUniform1f(this->theProgram, "fBitangent", (float)va_arg(uniformList, double));
}

void VertexVisualizerShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}