#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;
uniform mat4 mWorldMatrix;
uniform vec3 vLight;

out vec2 vUV;
out vec3 vNormal;
out vec3 vPosition;
out vec3 vLightPos;

void main(void)
{
	gl_Position = mMVP * vec4(position, 1.0f);
	vUV = uv;
	vNormal   = (mWorldMatrix * normal).xyz;
	vPosition = (mWorldMatrix * vec4(position, 1.0)).xyz;

	vLightPos = vLight - vPosition;
}