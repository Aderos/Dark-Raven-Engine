#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

out vec2 vUV;
out vec3 vPosition;
out vec3 vNormal;
out vec3 vEyeDir;
out vec3 vLightDir;

uniform mat4 mMVP;
uniform mat4 mViewMatrix;
uniform mat4 mWorldMatrix;
uniform mat4 mMV;
uniform vec3 vLight;

void main(){

	gl_Position =  mMVP * vec4(position,1);
	
	vPosition = (mWorldMatrix* vec4(position, 1)).xyz;
	vEyeDir   = normalize(vec3(0, 0, 0) - (mMV * vec4(position, 1)).xyz);
	vLightDir = normalize((mViewMatrix * vec4(vLight, 1)).xyz - (mMV * vec4(position, 1)).xyz);
	vNormal   = normalize((mMV * vec4(normal, 0)).xyz);

	vUV = uv;
}