#include "DepthShader.h"

DepthShader::DepthShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/Depth.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/Depth.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

DepthShader::~DepthShader()
{
}

void DepthShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void DepthShader::SetParameters(va_list uniformList)
{

	Matrix44f mMVP = va_arg(uniformList, Matrix44f);

	m_OpenGL->SetUniformMatrix4f(theProgram, "mMVP", mMVP.GetTranspose());

	m_OpenGL->BindActiveShadowTexture2D(va_arg(uniformList, GLuint));
	m_OpenGL->SetUniform1i(theProgram, "iTexture", 1);
}

void DepthShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}