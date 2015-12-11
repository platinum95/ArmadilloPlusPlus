#version 330

in vec3 vTextureCoords;

out vec4 FragColor;

uniform samplerCube uCubeMap;

const float fLowerLimit = -20.0;
const float fUpperLimit = 60.0;

layout (std140) uniform SkyFog
{
	vec4 vSkyColour;
	float fDensity;
	float fGradient;
};

void main() 
{
	vec4 vColour = texture(uCubeMap, vTextureCoords);

	float fFadeFactor = (vTextureCoords.y - fLowerLimit) / (fUpperLimit - fLowerLimit);
	fFadeFactor = clamp(fFadeFactor, 0.0, 1.0);

	FragColor = mix(vSkyColour, vColour, fFadeFactor);
}
