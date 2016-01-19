#version 400

layout(location = 0) in vec3 position;

uniform mat4 mMVP;

void main(void)
{
	gl_Position = mMVP * vec4(position, 1.0f);
}