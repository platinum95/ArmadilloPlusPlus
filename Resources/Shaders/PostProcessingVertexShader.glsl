#version 330

in vec2 vPosition;

out vec2 vFragTextureCoords;

void main()
{	
	gl_Position = vec4(vPosition, 0.0, 1.0);
	vFragTextureCoords = (vPosition + 1.0) / 2.0;
}