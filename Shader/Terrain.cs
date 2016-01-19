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
uniform int fHeight;

void main(void)
{
	vec4 vPosition = vec4(position.x, position.y, position.z, 1.0f);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vPosition;

	vVaryingNormal = normalize(inverse(transpose(worldMatrix)) * normal);
	vVaryingPosition = worldMatrix * vPosition;
	vVaryingLightDir = normalize(vLightDir - vVaryingPosition.xyz);

	vUV = uv;
}