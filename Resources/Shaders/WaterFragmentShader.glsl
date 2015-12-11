#version 330

in vec3 vFragPosition;
in vec2 vFragTextureCoords;
in float fDistance;
in vec4 vClipSpace;

out vec4 FragColor;

uniform sampler2D uReflectionTexture;
uniform sampler2D uRefractionTexture;
uniform sampler2D uDuDvTexture;
uniform sampler2D uNormalTexture;
uniform sampler2D uDepthTexture;

uniform float fNearPlane;
uniform float fFarPlane;
uniform float fDuDvOffset;
uniform vec3 vWaterColour;

const float fDistortionStrength = 0.02;
const float fShineDamper = 20.0;
const float fReflectivity = 0.3;
const float fWaterDepthFade = 3.0;
const float fWaterDistortionFade = 5.0;
const float fWaterMix = 0.95;
const float fFresnelReflection = 0.5;
const float fNormalUpwardStrength = 3.0;
const float fAmbient = 0.2;

struct Light
{
	vec4 vFirst;
	vec4 vSecond;
	vec4 vThird;
};

layout (std140) uniform LightData
{
	Light sLights[4];
};

layout (std140) uniform SkyFog
{
	vec4 vSkyColour;
	float fDensity;
	float fGradient;
};

layout (std140) uniform ViewData
{	
	mat4 mViewMatrix;
	mat4 mProjectionMatrix;
	vec3 vViewPosition;
};

Light CalculateLight(Light, vec3, vec3, vec3);
Light CalculatePointLight(Light, vec3, vec3, vec3);
Light CalculateSpotLight(Light, vec3, vec3, vec3);
Light CalculateDirectionalLight(Light, vec3, vec3);
vec4 ConvertLightToVec4(Light, vec4);

void main() 
{
	vec2 vDeviceSpace = (vClipSpace.xy/vClipSpace.w)/2.0 + 0.5;
	vec2 vReflectCoord = vec2(vDeviceSpace.x, -vDeviceSpace.y);
	vec2 vRefractCoord = vDeviceSpace;

	float fDepth = texture(uDepthTexture, vRefractCoord).r;
	float fFloorDistance = 2.0 * fNearPlane * fFarPlane / (fFarPlane + fNearPlane - (2.0 * fDepth - 1.0) * (fFarPlane - fNearPlane));
	float fWaterDistance = 2.0 * fNearPlane * fFarPlane / (fFarPlane + fNearPlane - (2.0 * gl_FragCoord.z - 1.0) * (fFarPlane - fNearPlane));
	float fWaterDepth = fFloorDistance - fWaterDistance;

	float fWaterDepthAlpha = clamp(fWaterDepth/fWaterDepthFade, 0.0, 1.0);

	vec2 vDistortionCoords = texture(uDuDvTexture, vec2(vFragTextureCoords.x + fDuDvOffset, vFragTextureCoords.y)).rg * 0.1;
	vDistortionCoords = vFragTextureCoords + vec2(vDistortionCoords.x, vDistortionCoords.y + fDuDvOffset);
	vec2 vDistortion = (texture(uDuDvTexture, vDistortionCoords).rg * 2.0 - 1.0) * fDistortionStrength * fWaterDepthAlpha/fWaterDistortionFade;

	vRefractCoord += vDistortion;
	vRefractCoord = clamp(vRefractCoord, 0.001, 0.999);
	vReflectCoord += vDistortion;
	vReflectCoord.x = clamp(vReflectCoord.x, 0.001, 0.999);
	vReflectCoord.y = clamp(vReflectCoord.y, -0.999, -0.001);

	vec4 vReflectColour = texture(uReflectionTexture, vReflectCoord);
	vec4 vRefractColour = texture(uRefractionTexture, vRefractCoord);

	vec4 vNormalTextureColour = texture(uNormalTexture, vDistortionCoords);
	vec3 vNormal = normalize(vec3(vNormalTextureColour.r * 2.0 - 1.0, vNormalTextureColour.b * fNormalUpwardStrength, vNormalTextureColour.g * 2.0 - 1.0));

	vec3 vToViewVector = normalize(vViewPosition - vFragPosition);
	float fFresnelFactor = dot(vToViewVector, vNormal);
	fFresnelFactor = clamp(pow(fFresnelFactor, fFresnelReflection), 0.0, 1.0);
			
	float fVisibility = exp(-pow( ( fDistance * fDensity) , fGradient) );
	fVisibility = clamp(fVisibility, 0.0, 1.0);
		
	FragColor = mix(vReflectColour, vRefractColour, fFresnelFactor);	
	FragColor = ConvertLightToVec4(CalculateLight(sLights[0], vNormal, vToViewVector, vFragPosition), FragColor);
	FragColor = mix(vec4(vWaterColour, 1.0), FragColor, fWaterMix);
	FragColor = mix(vSkyColour, FragColor, fVisibility);
	FragColor.a = fWaterDepthAlpha;	
}

vec4 ConvertLightToVec4(Light sLight, vec4 vColour)
{
	return (sLight.vFirst + sLight.vThird) * vColour + sLight.vSecond;
}

Light CalculateLight(Light sLight, vec3 vNormal, vec3 vToViewVector, vec3 vWorldPosition)
{
	Light result;
	if(int(sLight.vFirst.w) == 0)
	{
		result = CalculatePointLight(sLight, vNormal, vToViewVector, vWorldPosition);
	}
	else if(int(sLight.vFirst.w) == 1)
	{
		result = CalculateSpotLight(sLight, vNormal, vToViewVector, vWorldPosition);
	}
	else
	{
		result = CalculateDirectionalLight(sLight, vNormal, vToViewVector);
	}
	return result;
}

Light CalculatePointLight(Light sLight, vec3 vNormal, vec3 vToViewVector, vec3 vWorldPosition)
{
	vec3 uLightDirection = normalize(sLight.vFirst.xyz - vWorldPosition);		
	float fBrightness = max( dot(vNormal, uLightDirection), 0.0);
	vec3 vReflectedLight = reflect(-uLightDirection, vNormal);
	float fSpecularFactor = max( dot( vReflectedLight, vToViewVector ), 0.0);

	float fDistance = length(sLight.vFirst.xyz - vWorldPosition);
	float fAttenuation = sLight.vThird.x + sLight.vThird.y * fDistance + sLight.vThird.z * fDistance * fDistance;

	Light l;
	l.vFirst = vec4(fBrightness * sLight.vSecond.xyz, 1.0) / fAttenuation;
	l.vSecond = vec4(pow(fSpecularFactor, fShineDamper) * fReflectivity * sLight.vSecond.xyz, 0.0) / fAttenuation;
	l.vThird = l.vFirst * fAmbient / fAttenuation;
	return l;
}

Light CalculateSpotLight(Light sLight, vec3 vNormal, vec3 vToViewVector, vec3 vWorldPosition)
{
	vec3 uLightDirection = normalize(sLight.vFirst.xyz - vWorldPosition);		
	float fBrightness = max( dot(vNormal, uLightDirection), 0.0);
	vec3 vReflectedLight = reflect(-uLightDirection, vNormal);
	float fSpecularFactor = max( dot( vReflectedLight, vToViewVector ), 0.0);

	float fTheta = dot(uLightDirection, normalize(-sLight.vThird.xyz));
	float fEpsilon = sLight.vSecond.w - sLight.vThird.w;
	float fIntensity = clamp( (fTheta - sLight.vThird.w) / fEpsilon, 0.0, 1.0);

	float fDistance = length(sLight.vFirst.xyz - vWorldPosition);
	float fAttenuation = 1.0;// + 0.09 * fDistance + 0.032 * fDistance * fDistance;
	fAttenuation = 1.0 / fAttenuation * fIntensity;

	Light l;
	l.vFirst = vec4(fBrightness * sLight.vSecond.xyz, 1.0) * fAttenuation;
	l.vSecond = vec4(pow(fSpecularFactor, fShineDamper) * fReflectivity * sLight.vSecond.xyz, 0.0) * fAttenuation;
	l.vThird = l.vFirst * fAmbient * fAttenuation;
	return l;
}

Light CalculateDirectionalLight(Light sLight, vec3 vNormal, vec3 vToViewVector)
{
	vec3 uLightDirection = normalize(-sLight.vFirst.xyz);
	float fBrightness = max( dot(vNormal, uLightDirection), 0.0);
	vec3 vReflectedLight = reflect(-uLightDirection, vNormal);
	float fSpecularFactor = max( dot( vReflectedLight, vToViewVector ), 0.0);

	Light l;
	l.vFirst = vec4(fBrightness * sLight.vSecond.xyz, 1.0);	
	l.vSecond = vec4(pow(fSpecularFactor, fShineDamper) * fReflectivity * sLight.vSecond.xyz, 0.0);
	l.vThird = l.vFirst * fAmbient;
	return l;
}
