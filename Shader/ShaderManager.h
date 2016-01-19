#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

#include <vector>

#include "Shader.h"
#include "BasicShader.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "LambertShader.h"
#include "PhongShader.h"
#include "CookTorranceShader.h"
#include "Object2DShader.h"
#include "DissolveShader.h"
#include "ToonShader.h"
#include "SkyboxShader.h"
#include "BumpMappingShader.h"
#include "LambertTextureShader.h"
#include "TerrainShader.h"
#include "ParallaxMappingShader.h"
#include "ShadowMappingShader.h"
#include "GodraysShader.h"
#include "VertexVisualizerShader.h"
#include "ParkShader.h"
#include "ParkLampShader.h"
#include "DepthShader.h"
#include "GroundParkShader.h"
#include "TessellationShader.h"
#include "ShadowBasicShader.h"
#include "FrameShader.h"
#include "ComputeShader.h"
#include "AccelerationShader.h"
#include "ParticleShader.h"
#include "OpenGL.h"

using std::va_list;
using std::vector;

class ShaderManager
{
public:
	ShaderManager(OpenGL*);
	~ShaderManager();

	void Reset();

	void Initialize();
	void UseShader(GLT_SHADER, ...);

	void Shutdown();

private:
	OpenGL* m_OpenGL;

private:
	vector<Shader*> vShader;

};

#endif