#version 330

in vec2 vFragTextureCoords;

out vec4 FragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform sampler2D uDepthTexture0;
uniform float fMix1;
uniform float fMix2;

void main()
{	
	vec4 vDepthColour = texture(uDepthTexture0, vFragTextureCoords);
	float fDepthMix = log(length(vDepthColour.xyz));
	
	vec4 vTextureColour0 = texture(uTexture0, vFragTextureCoords);
	vec4 vTextureColour1 = texture(uTexture1, vFragTextureCoords);
	vec4 vTextureColour2 = texture(uTexture2, vFragTextureCoords);

	FragColor = mix(vTextureColour0, vTextureColour2, clamp(fDepthMix * fMix2, 0.0, 1.0)) + fMix1 * vTextureColour2; //vec4(vec3(fDepthMix), 1.0);
}