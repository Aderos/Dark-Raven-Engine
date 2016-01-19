#version 430

layout(location = 0) in vec3 position;

uniform mat4 mVP;

void main(void)
{
	gl_Position = mVP * vec4(position, 1.0f);
}