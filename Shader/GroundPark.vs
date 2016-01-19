#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;
uniform mat4 mWorldMatrix;
uniform vec3 vLight;

out vec2 vUV;
out vec3 vNormal;
out vec3 vTangent;
out vec3 vBitangent;
out vec3 vLightDir;

vec3 CalcTangent(vec3 vNormal)
{
	vec3 c1 = cross(vNormal, vec3(0.0, 0.0, 1.0));
	vec3 c2 = cross(vNormal, vec3(0.0, 1.0, 0.0));

	return length(c1) > length(c2) ? normalize(c1) : normalize(c2);
}

vec3 CalcBitangent(vec3 vNormal, vec3 vTangent)
{
	return normalize(cross(vNormal, vTangent));
}

void main(void)
{
	gl_Position = mMVP * vec4(position, 1.0f);

	vNormal    = normalize((mWorldMatrix * normal).xyz);
	vTangent   = normalize((mWorldMatrix * vec4(CalcTangent(normal.xyz), 0.0)).xyz);
	vBitangent = normalize((mWorldMatrix * vec4(CalcBitangent(normal.xyz, vTangent), 0.0)).xyz);
	vLightDir  = vLight - (mWorldMatrix * vec4(position, 1.0)).xyz;

	vUV = uv;
}