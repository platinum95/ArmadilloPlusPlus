#version 330

in vec2 vFragTextureCoords;

uniform sampler2D uFrameTexture;
uniform float fThreshold;

const vec3 vLuminanceVector = vec3(0.2125, 0.7154, 0.0721);

out vec4 FragColor;

void main()
{	
	vec4 vColour = texture(uFrameTexture, vFragTextureCoords);

	float fLuminance = max(0.0, dot(vLuminanceVector, vColour.rgb) - fThreshold);
	vColour.rgb *= sign(fLuminance);
	vColour.a = 1.0;
	FragColor = vColour;
}