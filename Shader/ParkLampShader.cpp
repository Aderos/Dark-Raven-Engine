#include "ParkLampShader.h"

ParkLampShader::ParkLampShader(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->m_ShaderCompiler = new ShaderCompiler(m_OpenGL);

	std::vector<GLuint> shaderList;
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetVertexShader(), "../Shader/ParkLamp.vs"));
	shaderList.push_back(this->m_ShaderCompiler->LoadShader(this->m_OpenGL->GetFragmentShader(), "../Shader/ParkLamp.ps"));

	this->theProgram = this->m_ShaderCompiler->CreateProgram(shaderList);
}

ParkLampShader::~ParkLampShader()
{
}

void ParkLampShader::SetShader()
{
	this->m_OpenGL->UseProgram(this->theProgram);
}

void ParkLampShader::SetParameters(va_list uniformList)
{
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mMVP", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformMatrix4f(this->theProgram, "mWorldMatrix", va_arg(uniformList, Matrix44f).GetTranspose());
	this->m_OpenGL->SetUniformVector3f(this->theProgram, "vLight", va_arg(uniformList, Vector3f).GetValue());

	this->m_OpenGL->BindActiveTexture2D(va_arg(uniformList, GLuint));
	this->m_OpenGL->SetUniform1i(this->theProgram, "iTexture", 0);
}

void ParkLampShader::Shutdown()
{
	if (this->m_ShaderCompiler)
	{
		this->m_ShaderCompiler->Shutdown();
		delete this->m_ShaderCompiler;
		this->m_ShaderCompiler = 0;
	}
}