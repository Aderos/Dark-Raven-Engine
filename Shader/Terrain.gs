#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

smooth in vec2 vUV[];
smooth in mat4 vVaryingNormal[];

smooth out vec2 UV;
smooth out vec4 vNormal;

void main(void)
{
	vec3 normal = normalize(cross(
	gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz,
	gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz));

	vec4 vecNormal = normalize(vVaryingNormal[0] * vec4(normal, 1.0f));
	
	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		
		vNormal = vecNormal;
		UV = vUV[i];
		
		EmitVertex();
	}
}