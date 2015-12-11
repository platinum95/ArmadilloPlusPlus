#version 330

in vec3 vPosition;
in vec2 vTextureCoords;
in vec3 vNormal;

flat out vec3 vFragNormal;
flat out vec3 vFragPosition;
flat out vec2 vFragTextureCoords;
flat out float fDistance;

uniform mat4 mModelMatrix;
uniform vec3 vTextureData;
uniform vec4 vClipPlane;

layout (std140) uniform ViewData
{	
	mat4 mViewMatrix;
	mat4 mProjectionMatrix;
	vec3 vViewPosition;
};

void main()
{
	vec4 vWorldPosition = mModelMatrix * vec4(vPosition.xyz, 1.0);
	vec4 vWorldNormal = mModelMatrix * vec4(vNormal.xyz, 0.0);
	vec4 vRelativePosition = mViewMatrix * vWorldPosition;
	gl_ClipDistance[0] = dot(vWorldPosition, vClipPlane);
	
	gl_Position = mProjectionMatrix * vRelativePosition;	

	vFragTextureCoords = vTextureCoords;//(vTextureCoords/vTextureData.z) + vTextureData.xy;
	
	fDistance = length(vRelativePosition.xyz);

	vFragNormal = normalize(vWorldNormal.xyz);
	vFragPosition = vWorldPosition.xyz;
}