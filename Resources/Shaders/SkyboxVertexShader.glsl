#version 330

in vec3 vPosition;

out vec3 vTextureCoords;

layout (std140) uniform ViewData
{	
	mat4 mViewMatrix;	
	mat4 mProjectionMatrix;
	vec3 vViewPosition;
};

void main()
{
	mat4 mEditViewMatrix = mViewMatrix;
	mEditViewMatrix[3][0] = 0;
	mEditViewMatrix[3][1] = 0;
	mEditViewMatrix[3][2] = 0;
	gl_Position = mProjectionMatrix * mEditViewMatrix * vec4(vPosition.xyz, 1.0);	
	vTextureCoords = vPosition;
}
