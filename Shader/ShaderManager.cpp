#include "ShaderManager.h"

ShaderManager::ShaderManager(OpenGL* m_OpenGL) : vShader()
{
	this->m_OpenGL = m_OpenGL;
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Initialize()
{
	this->vShader.push_back((Shader*)new BasicShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ColorShader(m_OpenGL));
	this->vShader.push_back((Shader*)new TextureShader(m_OpenGL));
	this->vShader.push_back((Shader*)new LambertShader(m_OpenGL));
	this->vShader.push_back((Shader*)new PhongShader(m_OpenGL));
	this->vShader.push_back((Shader*)new CookTorranceShader(m_OpenGL));
	this->vShader.push_back((Shader*)new Object2DShader(m_OpenGL));
	this->vShader.push_back((Shader*)new DissolveShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ToonShader(m_OpenGL));
	this->vShader.push_back((Shader*)new SkyboxShader(m_OpenGL));
	this->vShader.push_back((Shader*)new BumpMappingShader(m_OpenGL));
	this->vShader.push_back((Shader*)new LambertTextureShader(m_OpenGL));
	this->vShader.push_back((Shader*)new TerrainShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ParallaxMappingShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ShadowMappingShader(m_OpenGL));
	this->vShader.push_back((Shader*)new GodraysShader(m_OpenGL));
	this->vShader.push_back((Shader*)new VertexVisualizerShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ParkShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ParkLampShader(m_OpenGL));
	this->vShader.push_back((Shader*)new DepthShader(m_OpenGL));
	this->vShader.push_back((Shader*)new GroundParkShader(m_OpenGL));
	this->vShader.push_back((Shader*)new TessellationShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ShadowBasicShader(m_OpenGL));
	this->vShader.push_back((Shader*)new FrameShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ComputeShader(m_OpenGL));
	this->vShader.push_back((Shader*)new AccelerationShader(m_OpenGL));
	this->vShader.push_back((Shader*)new ParticleShader(m_OpenGL));
}

void ShaderManager::UseShader(GLT_SHADER index, ...)
{
	va_list uniformList;
	va_start(uniformList, index);

	this->vShader[index]->SetShader();
	this->vShader[index]->SetParameters(uniformList);

	va_end(uniformList);
}

void ShaderManager::Shutdown()
{
	for (unsigned int i = 0; i < vShader.size(); i++)
	{
		this->vShader[i]->Shutdown();
		delete vShader[i];
		this->vShader[i] = 0;
	}
}

void ShaderManager::Reset()
{
	m_OpenGL->UseProgram(0);
}