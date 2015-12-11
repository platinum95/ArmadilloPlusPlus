#include "Osiris.h"
#include <gl\glew.h>

namespace Armadillo
{
	namespace Osiris
	{
		std::string Name = "Armadillo";

		//Display
		int DisplayWidth = 1600;
		int DisplayHeight = 900;
		int DisplayFrame = 0;
		float DisplayFrameTime = 0;
		float DisplayAspectRatio = (float)DisplayWidth/(float)DisplayHeight;
		float DisplayFrameRate = 60;
		float DisplayNearPlane = 1.0f;
		float DisplayFarPlane = 1000.0f;
		float DisplayFieldOfView = ConstantPi/2;
		bool DisplayFullscreen = false;

		//Graphics
		int DrawType = GL_TRIANGLES;
		int DrawTerrainIndexBuffer = 0;
		std::string DrawTerrainVertexBufferName = "VT_";
		std::string DrawTerrainIndexBufferName = "VI_";
		std::string DrawTerrainVertexBufferDelimiter = ",";

		//Maths
		double ConstantE = 2.71828182845904523536028747135266249;
		double ConstantPi = 3.14159265358979323846264338327950288;

		//Biome
		int BiomeCount = 14;
		Armadillo::World::BiomeType BiomeGlobalType = Armadillo::World::BiomeType::TemperateDeciduousForest;

		//Terrain
		int TerrainIndexBufferCount = 6;
		bool TerrainGenerationEnable = true;
		int TerrainGenerationBoost = 1;
		int TerrainStoredDataPolicy = 20;

		//World
		Armadillo::World::Seed WorldSeed = Armadillo::World::Seed(33, 33, 8, 48, 20, 0.5f, 4);
		float WorldTime = 0;
		float WorldGravity = 9.81f;
		bool WorldGravityEnable = true;
		int WorldWaveDisplacement = 0;
		float WorldWaterHeight = 40.0f;
		float WorldMaxHeight = 10000.0f;

		//Player
		bool FreeViewEnable = true;
		bool FreeCameraEnable = false;
		float PlayerHeight = 3.0f;
		float PlayerVelocity = 1.0f;
		float PlayerAngularVelocity = 0.025f;
		float PlayerCameraSensitivity = 0.001f;

		//Default Uniform Buffers
		std::string UniformBufferViewData = "ViewData";
		std::string UniformBufferLightData = "LightData";
		std::string UniformBufferSkyFog = "SkyFog";
		std::string UniformBufferTerrainColours = "TerrainColours";
		std::string UniformBufferTerrainSelectors = "TerrainSelectors";
		std::string FloatBufferSkybox = "Skybox";

		//Water Buffers
		std::string FloatBufferWaterQuad = "WaterQuad";
		std::string FrameBufferReflection = "WaterReflection";
		std::string FrameBufferRefraction = "WaterRefraction";
		
		//HDR 
		bool DrawEffectHDREnable = false;
		float DrawEffectHDRExposure = 2.2f;

		//Post Processing
		bool PostEffectBloomEnable = false;
		float PostEffectBloomThreshold = 0.8f;
		float PostEffectBloomRadius = 2.0f;
		float PostEffectBloomMix = 0.45f;

		bool PostEffectFieldBlurEnable = false;
		float PostEffectFieldBlurRadius = 2.0f;
		float PostEffectFieldBlurMix = 1.0f;


		std::string FloatBufferFrameQuad = "FrameQuad";
		std::string FrameBufferTextureDepth0 = "FBTDBoth0";
		std::string FrameBufferTextureDepthB0 = "FBTDB0";
		std::string FrameBufferTextureDepthT0 = "FBTDT0";
		std::string FrameBufferTexture0 = "FBT0";
		std::string FrameBufferTexture1 = "FBT1";
		std::string FrameBufferTexture2 = "FBT2";


		//Shaders
		std::string ShaderEntity = "EntityShader";
		std::string ShaderEntityVertex = "../Resources/Shaders/EntityVertexShader.glsl";
		std::string ShaderEntityFragment = "../Resources/Shaders/EntityFragmentShader.glsl";

		std::string ShaderTerrain = "TerrainShader";
		std::string ShaderTerrainVertex = "../Resources/Shaders/TerrainVertexShader.glsl";
		std::string ShaderTerrainFragment = "../Resources/Shaders/TerrainFragmentShader.glsl";

		std::string ShaderSkybox = "SkyboxShader";
		std::string ShaderSkyboxVertex = "../Resources/Shaders/SkyboxVertexShader.glsl";
		std::string ShaderSkyboxFragment = "../Resources/Shaders/SkyboxFragmentShader.glsl";

		std::string ShaderWater = "WaterShader";
		std::string ShaderWaterVertex = "../Resources/Shaders/WaterVertexShader.glsl";
		std::string ShaderWaterFragment = "../Resources/Shaders/WaterFragmentShader.glsl";

		std::string ShaderGaussian = "GaussianShader";
		std::string ShaderGaussianVertex = "../Resources/Shaders/PostProcessingVertexShader.glsl";
		std::string ShaderGaussianFragment = "../Resources/Shaders/GaussianLinearFragmentShader.glsl";

		std::string ShaderBloom = "BloomShader";
		std::string ShaderBloomVertex = "../Resources/Shaders/PostProcessingVertexShader.glsl";
		std::string ShaderBloomFragment = "../Resources/Shaders/BloomFragmentShader.glsl";

		std::string ShaderMixture = "MixtureShader";
		std::string ShaderMixtureVertex = "../Resources/Shaders/PostProcessingVertexShader.glsl";
		std::string ShaderMixtureFragment = "../Resources/Shaders/MixtureFragmentShader.glsl";

		std::string ShaderHDR = "MixtureShader";
		std::string ShaderHDRVertex = "../Resources/Shaders/PostProcessingVertexShader.glsl";
		std::string ShaderHDRFragment = "../Resources/Shaders/HDRFragmentShader.glsl";

		//Files
		std::string PathResources = "../Resources/";
		std::string PathTextures = "../Resources/Textures/";
		std::string PathShaders = "../Resources/Shaders/";
		std::string PathModels = "../Resources/Models/";
		std::string PathWorld = "../World/";

		std::string ExtensionImage = ".png";
		std::string ExtensionModel = ".obj";

		std::string FileEntities = "../World/Entities.txt";
		std::string FileEntityTypes = "../World/EntityTypes.txt";
		std::string FileResources = "../Resources/Resources.txt";
	}
}