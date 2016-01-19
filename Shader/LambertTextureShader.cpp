#include "LambertTextureShader.h"

LambertTextureShader::LambertTextureShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetVertexShader(), "../Shader/LambertTexture.vs"));
	shaderList.push_back(m_ShaderCompiler->LoadShader(m_OpenGL->GetFragmentShader(), "../Shader/LambertTexture.ps"));

	this->theProgram = m_ShaderCompiler->CreateProgram(shaderList);
}

LambertTextureShader::~LambertTextureShader()
{
}

void LambertTextureShader::SetShader()
{
	m_OpenGL->UseProgram(theProgram);
}

void LambertTextureShader::SetParameters(va_list uniformList)
{
	// Set the world matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "worldMatrix", va_arg(uniformList, Matrix44f).GetMatrix());

	// Set the view matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "viewMatrix", va_arg(uniformList, Matrix44f).GetMatrix());

	// Set the projection matrix in the vertex shader.
	m_OpenGL->SetUniformMatrix4f(theProgram, "projectionMatrix", va_arg(uniformList, Matrix44f).GetMatrix());

	// Set the color in fragment shader.
	m_OpenGL->SetUniformVector4f(theProgram, "vColor", va_arg(uniformList, Vector4f).GetValue());

	// Set the ambient in fragment shader.
	m_OpenGL->SetUniformVector4f(theProgram, "vAmbient", va_arg(uniformList, Vector4f).GetValue());

	// Set the light dir in fragment shader.
	m_OpenGL->SetUniformVector3f(theProgram, "vLightDir", va_arg(uniformList, Vector3f).GetValue());

	// Set active the texture in the fragment shader.
	m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));

	// Set the texture in the fragment shader.
	m_OpenGL->SetUniform1i(theProgram, "Texture", 0);
}

void LambertTextureShader::Shutdown()
{
	if (m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}