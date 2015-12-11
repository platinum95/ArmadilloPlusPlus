#version 330

flat in float fDistance;
flat in vec3 vFragNormal;
flat in vec3 vFragPosition;

out vec4 FragColor;

const float fShineDamper = 20.0;
const float fReflectivity = 0.3;
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

layout (std140) uniform TerrainColours
{
	vec4 vTerrainColours[13];	
};

layout (std140) uniform TerrainSelectors
{
	vec4 vTerrainZones[4];
};

Light CalculateLight(Light, vec3, vec3, vec3);
Light CalculatePointLight(Light, vec3, vec3, vec3);
Light CalculateSpotLight(Light, vec3, vec3, vec3);
Light CalculateDirectionalLight(Light, vec3, vec3);
vec4 ConvertLightToVec4(Light, vec4);

void main()
{
	float fVisibility = exp(-pow( ( fDistance * fDensity) , fGradient));
	fVisibility = clamp(fVisibility, 0.0, 1.0);	

	vec3 vToViewVector = normalize(vViewPosition - vFragPosition);

	FragColor = ConvertLightToVec4(CalculateLight(sLights[0], vFragNormal, vToViewVector, vFragPosition), vTerrainColours[int(vTerrainZones[0].w)]);	
	FragColor = mix(vSkyColour, FragColor, fVisibility);
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

	Light l;
	l.vFirst = vec4(fBrightness * sLight.vSecond.xyz, 1.0) / fAttenuation * fIntensity;
	l.vSecond = vec4(pow(fSpecularFactor, fShineDamper) * fReflectivity * sLight.vSecond.xyz, 0.0) / fAttenuation * fIntensity;
	l.vThird = l.vFirst * fAmbient / fAttenuation * fIntensity;
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
