#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;
uniform mat4 mWorldMatrix;
uniform mat4 mDepthMatrix;
uniform vec3 vLight;

out vec2 vUV;
out vec3 vLightPos;
out vec3 vNormal;
out vec3 vPosition;
out vec3 vLightDir;
out vec4 ShadowCoord;

void main(void)
{
	gl_Position = mMVP * vec4(position, 1.0);

	mat4 DepthBiasMVP = mDepthMatrix * mMVP;
	ShadowCoord = DepthBiasMVP * vec4(vLight, 1.0) * vec4(position, 1.0);

	vLightPos = vLight;
	
	vLightDir = normalize(vLight - (mWorldMatrix * vec4(position, 1.0)).xyz);
	vNormal   = normalize(mWorldMatrix * normal).xyz;
	vPosition = normalize(mWorldMatrix * vec4(position, 1.0)).xyz;
	vUV = uv;
}