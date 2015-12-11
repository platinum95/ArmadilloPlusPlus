#version 330

in vec2 vFragTextureCoords;

out vec4 FragColor;

uniform sampler2D uFrameTexture;
uniform float fRadius;
uniform float fResolution;
uniform vec2 vDirection;

const int fPass = 4;

const float fWeights[4] = {
	0.0162162162,
	0.0540540541,
	0.1216216216,
	0.1945945946
};

void main()
{	
	float fBlur = fRadius / fResolution;

	vec4 vTextureColour = texture(uFrameTexture, vFragTextureCoords);
	FragColor = vTextureColour * 0.2270270270;	

	for(int i = -fPass; i <= 1; i++)
	{
		FragColor += texture(uFrameTexture, vec2(vFragTextureCoords.x + i * fBlur * vDirection.x, vFragTextureCoords.y + i * fBlur * vDirection.y)) * fWeights[i+fPass];
	}
	for(int i = 1; i <= fPass; i++)
	{
		FragColor += texture(uFrameTexture, vec2(vFragTextureCoords.x + i * fBlur * vDirection.x, vFragTextureCoords.y + i * fBlur * vDirection.y)) * fWeights[fPass-i];
	}

	//FragColor = vTextureColour;//mix(FragColor, vTextureColour, 0.5);
}