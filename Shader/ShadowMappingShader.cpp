#include "ShadowMappingShader.h"

ShadowMappingShader::ShadowMappingShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/ShadowMapping.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/ShadowMapping.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

ShadowMappingShader::~ShadowMappingShader()
{
}

void ShadowMappingShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void ShadowMappingShader::SetParameters(va_list uniformList)
{
	Matrix44f biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);

	m_OpenGL->SetUniformMatrix4f(theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	m_OpenGL->SetUniformMatrix4f(theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	m_OpenGL->SetUniformMatrix4f(theProgram, "mDepthMatrix", biasMatrix.GetTranspose());
	m_OpenGL->SetUniformVector3f(theProgram, "vLight", va_arg(uniformList, Vector3f).GetValue());

	// Set active the texture in the fragment shader.
	m_OpenGL->BindActiveShadowTexture2D(va_arg(uniformList, GLuint));

	// Set the texture in the fragment shader.
	m_OpenGL->SetUniform1i(theProgram, "iTexture", 1);
}

void ShadowMappingShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}