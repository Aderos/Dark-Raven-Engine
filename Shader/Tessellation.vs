#version 410

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mWorldMatrix;

out vec3 vPosition_CS;
out vec2 vUV_CS;
out vec3 vNormal_CS;

void main(void)
{
	vPosition_CS = normalize((mWorldMatrix * vec4(position, 0.0)).xyz);
	vNormal_CS	 = normalize((mWorldMatrix * vec4(normal, 0.0)).xyz);
	vUV_CS		 = uv;
}