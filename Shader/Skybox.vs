#version 400

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;

out vec3 vUV;

void main(void)
{
	gl_Position = mMVP * vec4(position, 1.0f);

	vUV = normalize(position.xyz);
}