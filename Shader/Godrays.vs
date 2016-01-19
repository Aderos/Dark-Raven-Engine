#version 400

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 uv;

uniform vec3 vLight;

out vec2 vUV;
out vec2 vLPOS;

void main(void)
{
	//vec4 vPos = vec4(position.x * 2.0, position.y * 2.0, 0.0, 1.0);
	//gl_Position = vPos;

	//vLPOS = vec2(vLight.x / 1024, vLight.y / 800) - 0.5;

	vUV = uv;
}