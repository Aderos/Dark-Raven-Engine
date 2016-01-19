#include "ShaderCompiler.h"

ShaderCompiler::ShaderCompiler(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
}

char* ShaderCompiler::LoadShaderSourceFile(char* cFilename)
{
	ifstream iFin;
	int iFileSize = 0;
	char cInput;
	char* cBuffer;
	
	iFin.open(cFilename);
	if (iFin.fail()) return 0; 
	iFin.get(cInput);

	while (!iFin.eof())
	{
		iFileSize++;
		iFin.get(cInput);
	}

	iFin.close();

	cBuffer = new char[iFileSize + 1];
	if (!cBuffer) { return 0; }

	iFin.open(cFilename);
	iFin.read(cBuffer, iFileSize);
	iFin.close();
	
	cBuffer[iFileSize] = '\0';

	return cBuffer;
}

bool ShaderCompiler::OutputLinkerErrorMessage(unsigned int uiProgramID)
{
	cout << "Error compiling linker." << endl;
	cout << this->m_OpenGL->GetProgramInfoLog(uiProgramID) << endl;
	return false;
}

bool ShaderCompiler::OutputShaderErrorMessage(unsigned int uiShaderID)
{
	cout << "Error compiling shader." << endl;
	cout << this->m_OpenGL->GetShaderInfoLog(uiShaderID) << endl;
	return false;
}

GLuint ShaderCompiler::LoadShader(GLenum eShaderType, char* cFilename)
{
	GLuint uiShader;
	const char* cShaderBuffer;

	if (!(cShaderBuffer = LoadShaderSourceFile(cFilename)))
		return false;

	this->m_OpenGL->CreateShader(uiShader, eShaderType, cShaderBuffer);

	delete[] cShaderBuffer;
	cShaderBuffer = 0;

	return uiShader;
}

GLuint ShaderCompiler::CreateProgram(std::vector<GLuint> vShaderList)
{
	for (unsigned int i = 0; i < vShaderList.size(); i++)
	{
		this->vShaderList.push_back(vShaderList[i]);

		if (!this->m_OpenGL->CompileShader(vShaderList[i]))
			return OutputShaderErrorMessage(vShaderList[i]);
	}

	this->m_OpenGL->CreateProgram(this->uiShaderProgram);
	this->m_OpenGL->AttachShaders(this->uiShaderProgram, this->vShaderList);
	
	if (!this->m_OpenGL->LinkProgram(this->uiShaderProgram))
		return OutputLinkerErrorMessage(this->uiShaderProgram);

	return this->uiShaderProgram;
}

void ShaderCompiler::Shutdown()
{
	this->m_OpenGL->DeleteShaders(this->uiShaderProgram, this->vShaderList);
	this->m_OpenGL->DeleteProgram(this->uiShaderProgram);
}