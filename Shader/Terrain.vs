#version 400

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 uv;

uniform mat4 mMVP;
uniform float fHeight;

out vec2 vUV;

void main(void)
{
	vec4 vPosition = vec4(position.x, position.y * fHeight, position.z, 1.0f);
	gl_Position = mMVP * vPosition;
	
	vUV = uv;
}