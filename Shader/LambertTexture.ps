#version 400

smooth in vec2 vUV;
smooth in vec4 vVaryingPosition;
smooth in vec4 vVaryingNormal;
smooth in vec3 vVaryingLightDir;

out vec4 outputColor;

uniform sampler2D Texture;
uniform vec4 vAmbient;
uniform vec4 vColor;

void main(void)
{
	float diff = max(0.0, dot(normalize(vVaryingNormal.xyz), vVaryingLightDir));
	outputColor = vec4(texture2D(Texture, vUV).rgb * diff, vColor.a);
	outputColor += vAmbient;
}