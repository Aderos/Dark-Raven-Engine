#version 150
layout(triangles) in;
layout(triangles_strip, max_vertices=3) out;

smooth in vec2 vUV;
smooth in vec4 vVaryingPosition;
smooth in vec4 vVaryingNormal;

smooth out vec2 vxUV;
smooth out vec4 vxVaryingPosition;
smooth out vec4 vxVaryingNormal;

void main(void)
{
	for(int i=0; i<gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;

		vxVaryingPosition = vVaryingPosition;
		vxVaryingNormal = vVaryingNormal;
		vxUV = vUV;

		EmitVertex();
	}
}