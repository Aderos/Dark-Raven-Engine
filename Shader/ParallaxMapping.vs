#version 400

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;
uniform mat4 mMV;
uniform mat4 mViewMatrix;
uniform mat4 mWorldMatrix;
uniform vec3 vLightPos;
uniform vec3 vEyePos;

out vec2 vUV;
out vec3 vLightTangentSpace;
out vec3 vEyeTangentSpace;

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

	//vPosition = (mWorldMatrix* vec4(position, 1)).xyz;
	//vEyeDir   = normalize(vec3(0, 0, 0) - (mMV * vec4(position, 1)).xyz);
	//vLightDir = normalize((mViewMatrix * vec4(vLight, 1)).xyz - (mMV * vec4(position, 1)).xyz);
	//vNormal   = normalize((mMV * vec4(normal, 0)).xyz);

	vec3 vNormalP    = normalize((mMV * vec4(normal, 0.0)).xyz);
	vec3 vWorldP     = normalize((mWorldMatrix * vec4(position, 1.0)).xyz);
	vec3 vTangentP   = normalize((mMV * vec4(CalcTangent(normal), 0.0)).xyz);
	vec3 vBitangentP = normalize((mMV * vec4(CalcBitangent(normal, vTangentP), 0.0)).xyz);
	
	vec3 vWorldDirectionToLight  = normalize((mViewMatrix * vec4(vLightPos, 1)).xyz - (mMV * vec4(position, 1)).xyz);
	vec3 vWorldDirectionToCamera = normalize(vec3(0, 0, 0) - (mMV * vec4(position, 1)).xyz);

	//vec3 vNormalP    = normalize((mWorldMatrix * vec4(normal, 0.0)).xyz);
	//vec3 vWorldP     = normalize((mWorldMatrix * vec4(position, 0.0)).xyz);
	//vec3 vTangentP   = normalize((mWorldMatrix * vec4(CalcTangent(normal), 0.0)).xyz);
	//vec3 vBitangentP = normalize((mWorldMatrix * vec4(CalcBitangent(normal, vTangentP), 0.0)).xyz);

	//vec3 vWorldDirectionToLight  = normalize(vWorldP - vLightPos);
	//vec3 vWorldDirectionToCamera = normalize(vWorldP - vEyePos);

	vLightTangentSpace = vec3(
	dot(vWorldDirectionToLight, vTangentP),
	dot(vWorldDirectionToLight, vBitangentP),
	dot(vWorldDirectionToLight, vNormalP));

	vEyeTangentSpace = vec3(
	dot(vWorldDirectionToCamera, vTangentP),
	dot(vWorldDirectionToCamera, vBitangentP),
	dot(vWorldDirectionToCamera, vNormalP));

	vUV = uv;
}