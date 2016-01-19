#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 uv;

smooth out vec2 vUV;
smooth out vec4 vVaryingPosition;
smooth out vec4 vVaryingNormal;
smooth out vec3 vVaryingLightDir;

uniform vec3 vLightDir;
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(position, 1.0f);

	vVaryingNormal = normalize(inverse(transpose(worldMatrix)) * normal);
	vVaryingPosition = worldMatrix * vec4(position, 1.0);
	vVaryingLightDir = normalize(vLightDir - vVaryingPosition.xyz);

	vUV = uv;
}