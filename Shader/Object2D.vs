#version 400

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 uv;

smooth out vec2 vVaryingUV;

uniform int iWidth;
uniform int iHeight;

void main(void)
{
	int ScreenWidth = iWidth / 2;
	int ScreenHeight = iHeight / 2;
	
	vec2 vertexPosition = (position.xy - vec2(ScreenWidth, ScreenHeight)) / vec2(ScreenWidth, ScreenHeight);
	gl_Position = vec4(vertexPosition, 0, 1);

	vVaryingUV = uv;
}