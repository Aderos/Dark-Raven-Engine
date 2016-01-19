#include "GodraysShader.h"

GodraysShader::GodraysShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	//shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/Godrays.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/Godrays.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

GodraysShader::~GodraysShader()
{
}

void GodraysShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void GodraysShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vLight", va_arg(uniformList, Vector3f).GetValue());

	m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	m_OpenGL->SetUniform1i(theProgram, "iTexture", 0);
	
	//m_OpenGL->SetUniform1f(theProgram, "exposure", (float)va_arg(uniformList, double));
	//m_OpenGL->SetUniform1f(theProgram, "decay", (float)va_arg(uniformList, double));
	//m_OpenGL->SetUniform1f(theProgram, "density", (float)va_arg(uniformList, double));
	//m_OpenGL->SetUniform1f(theProgram, "weight", (float)va_arg(uniformList, double));
}

void GodraysShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}