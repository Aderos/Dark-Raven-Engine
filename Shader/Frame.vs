#version 430

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;
		
out vec2 vUV;

void main() 
{
	int ScreenWidth = 1280 / 2;
	int ScreenHeight = 720 / 2;
	
	vec2 vertexPosition = (position.xy - vec2(ScreenWidth, ScreenHeight)) / vec2(ScreenWidth, ScreenHeight);
	gl_Position = vec4(vertexPosition, 0, 1);

	vUV = uv;
}