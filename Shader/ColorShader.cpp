#include "ColorShader.h"

ColorShader::ColorShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/Color.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/Color.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

ColorShader::~ColorShader()
{
}

void ColorShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void ColorShader::SetParameters(va_list uniformList)
{	
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector4f(this->theProgram, "vColor", va_arg(uniformList, Vector4f).GetValue());
}

void ColorShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}

	this->m_OpenGL->DeleteProgram(this->theProgram);
}