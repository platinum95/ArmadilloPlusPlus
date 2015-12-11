#pragma once
#include <string>
#include "World/Seed.h"
#include "World/Biome.h"

namespace Armadillo
{
	namespace Osiris
	{
		extern std::string Name;

		//Display
		extern int DisplayWidth;
		extern int DisplayHeight;
		extern int DisplayFrame;
		extern float DisplayAspectRatio;
		extern float DisplayFrameRate;
		extern float DisplayNearPlane;
		extern float DisplayFarPlane;
		extern float DisplayFieldOfView;
		extern float DisplayFrameTime;
		extern bool DisplayFullscreen;

		//Graphics
		extern int DrawType;
		extern int DrawTerrainIndexBuffer;
		extern std::string DrawTerrainVertexBufferName;
		extern std::string DrawTerrainIndexBufferName;
		extern std::string DrawTerrainVertexBufferDelimiter;

		//Maths
		extern double ConstantE;
		extern double ConstantPi;

		//Biome
		extern int BiomeCount;
		extern Armadillo::World::BiomeType BiomeGlobalType;

		//Terrain
		extern Armadillo::World::Seed WorldSeed;
		extern int TerrainIndexBufferCount;
		extern bool TerrainGenerationEnable;
		extern int TerrainGenerationBoost;
		extern int TerrainStoredDataPolicy;

		//World
		extern float WorldTime;
		extern float WorldGravity;
		extern bool WorldGravityEnable;
		extern int WorldWaveDisplacement;
		extern float WorldWaterHeight;
		extern float WorldMaxHeight;	

		//Player
		extern bool FreeViewEnable;
		extern bool FreeCameraEnable;
		extern float PlayerHeight;
		extern float PlayerVelocity;
		extern float PlayerAngularVelocity;
		extern float PlayerCameraSensitivity;

		//Default Buffer Names
		extern std::string UniformBufferViewData;
		extern std::string UniformBufferLightData;
		extern std::string UniformBufferSkyFog;
		extern std::string UniformBufferTerrainColours;
		extern std::string UniformBufferTerrainSelectors;
		extern std::string FloatBufferSkybox;

		//Water Buffers
		extern std::string FloatBufferWaterQuad;
		extern std::string FrameBufferReflection;
		extern std::string FrameBufferRefraction;

		//HDR 
		extern bool DrawEffectHDREnable;
		extern float DrawEffectHDRExposure;

		//Post Processing
		extern bool PostEffectBloomEnable;
		extern float PostEffectBloomThreshold;
		extern float PostEffectBloomRadius;
		extern float PostEffectBloomMix;

		extern bool PostEffectFieldBlurEnable;
		extern float PostEffectFieldBlurRadius;
		extern float PostEffectFieldBlurMix;

		extern std::string FloatBufferFrameQuad;
		extern std::string FrameBufferTextureDepth0;
		extern std::string FrameBufferTextureDepthB0;
		extern std::string FrameBufferTextureDepthT0;
		extern std::string FrameBufferTexture0;
		extern std::string FrameBufferTexture1;
		extern std::string FrameBufferTexture2;

		//Shaders
		extern std::string ShaderEntity;
		extern std::string ShaderEntityVertex;
		extern std::string ShaderEntityFragment;

		extern std::string ShaderTerrain;
		extern std::string ShaderTerrainVertex;
		extern std::string ShaderTerrainFragment;

		extern std::string ShaderSkybox;
		extern std::string ShaderSkyboxVertex;
		extern std::string ShaderSkyboxFragment;

		extern std::string ShaderWater;
		extern std::string ShaderWaterVertex;
		extern std::string ShaderWaterFragment;

		extern std::string ShaderGaussian;
		extern std::string ShaderGaussianVertex;
		extern std::string ShaderGaussianFragment;

		extern std::string ShaderBloom;
		extern std::string ShaderBloomVertex;
		extern std::string ShaderBloomFragment;

		extern std::string ShaderMixture;
		extern std::string ShaderMixtureVertex;
		extern std::string ShaderMixtureFragment;

		extern std::string ShaderHDR;
		extern std::string ShaderHDRVertex;
		extern std::string ShaderHDRFragment;

		//Files
		extern std::string PathResources;
		extern std::string PathTextures;
		extern std::string PathShaders;
		extern std::string PathModels;
		extern std::string PathWorld;

		extern std::string ExtensionImage;
		extern std::string ExtensionModel;

		extern std::string FileEntities;
		extern std::string FileEntityTypes;
		extern std::string FileResources;
	}
}