#version 330
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 4) in vec3 tangent;
layout(location = 5) in vec3 bitangent;

out Vertex
{
	vec3 vNormal;
	vec3 vTangent;
	vec3 vBitangent;
} vVertex;

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

void main()
{
	gl_Position = vec4(position, 1.0f);

	vVertex.vNormal = normal;
	vVertex.vTangent = CalcTangent(vVertex.vNormal);
	vVertex.vBitangent = CalcBitangent(vVertex.vNormal, vVertex.vTangent);
}