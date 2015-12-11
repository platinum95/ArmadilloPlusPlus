#version 330

in vec2 vFragTextureCoords;

uniform sampler2D uFrameTexture;
uniform float fExposure;

out vec4 FragColor;

void main()
{             
    vec3 vHDRColour = texture(uFrameTexture, vFragTextureCoords).rgb;
  
    vec3 vMappedColour = vHDRColour / (vHDRColour + vec3(1.0));

    vMappedColour = pow(vMappedColour, vec3(1.0 / fExposure));
  
    FragColor = vec4(vMappedColour, 1.0);
}   