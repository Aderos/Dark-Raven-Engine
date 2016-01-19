#version 330
layout (triangles) in;

layout(line_strip, max_vertices = 18) out;

uniform mat4 mMVP;
uniform int bNormal;
uniform int bTangent;
uniform int bBitangent;

uniform float fNormal;
uniform float fTangent;
uniform float fBitangent;

in Vertex
{
	vec4 vNormal;
	vec4 vTangent;
	vec4 vBitangent;
} vVertex[];

out vec4 vVertexColorPS;

void main()
{
	for(int i=0; i < gl_in.length(); i++)
	{
		vec3 P = gl_in[i].gl_Position.xyz;
		vec3 N = vVertex[i].vNormal.xyz;
		vec3 T = vVertex[i].vTangent.xyz;
		vec3 B = vVertex[i].vBitangent.xyz;

		if(bNormal != 0)
		{
			// Normal
			gl_Position = mMVP * vec4(P, 1.0);
			vVertexColorPS = vec4(0.0, 0.0, 1.0, 1.0);
			EmitVertex();

			gl_Position = mMVP * vec4(P + N * fNormal, 1.0);
			vVertexColorPS = vec4(0.0, 0.0, 1.0, 1.0);
			EmitVertex();

			EndPrimitive();
		}
		
		if(bTangent != 0)
		{
			// Tangent
			gl_Position = mMVP * vec4(P, 1.0);
			vVertexColorPS = vec4(0.0, 1.0, 0.0, 1.0);
			EmitVertex();

			gl_Position = mMVP * vec4(P + T * fTangent, 1.0);
			vVertexColorPS = vec4(0.0, 1.0, 0.0, 1.0);
			EmitVertex();

			EndPrimitive();
		}
		
		if(bBitangent != 0)
		{
			// Bitangent
			gl_Position = mMVP * vec4(P, 1.0);
			vVertexColorPS = vec4(1.0, 0.0, 0.0, 1.0);
			EmitVertex();

			gl_Position = mMVP * vec4(P + B * fBitangent, 1.0);
			vVertexColorPS = vec4(1.0, 0.0, 0.0, 1.0);
			EmitVertex();

			EndPrimitive();
		}
	}
}