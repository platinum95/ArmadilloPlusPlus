#version 330

in vec2 vFragTextureCoords;

out vec4 FragColor;

uniform sampler2D uFrameTexture;
uniform vec2 vDirection;
uniform float fResolution;

const float fWeights[3] = { 0.2270270270, 0.3162162162, 0.0702702703 };
const float fOffsets[3] = { 0.0, 1.3846153846, 3.2307692308 };

void main()
{	
	vec2 vDeviceSpace = vFragTextureCoords;

	FragColor = texture(uFrameTexture, vDeviceSpace/fResolution ) * fWeights[0];

	for(int i = 1; i < 3; i++)
	{
		FragColor += texture(uFrameTexture, ( vDeviceSpace + vDirection * fOffsets[i] )/fResolution) * fWeights[i];

		FragColor += texture(uFrameTexture, ( vDeviceSpace - vDirection * fOffsets[i] )/fResolution) * fWeights[i];
	}	
}