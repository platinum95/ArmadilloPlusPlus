#version 330

in vec2 vPosition;

out vec3 vFragPosition;
out vec2 vFragTextureCoords;
out float fDistance;
out vec4 vClipSpace;

const float fTiling = 3.0;

uniform mat4 mModelMatrix;

layout (std140) uniform ViewData
{
	mat4 mViewMatrix;
	mat4 mProjectionMatrix;
	vec3 vViewPosition;
};

void main()
{
	vec4 vWorldPosition = mModelMatrix * vec4(vPosition.x, 0.0, vPosition.y, 1.0);	
	vec4 vRelativePosition = mViewMatrix * vWorldPosition;		
	
	float fDistance = length(vRelativePosition.xyz);

	vClipSpace = mProjectionMatrix * vRelativePosition;
	gl_Position = vClipSpace;

	vFragTextureCoords = (vPosition + 0.5)/2.0 * fTiling; //vec2(vPosition.x/2.0 + 0.5, vPosition.y/2.0 + 0.5) * fTiling;
	vFragPosition = vWorldPosition.xyz;
}
