#pragma once
#include "../Management/Manager.h"
#include "Skybox.h"
#include "Fermat.h"

#include <vector>
#include <map>

namespace Armadillo
{
	namespace World
	{
		class Light;
		class Entity;
		class Landscape;
		class TerrainManager;
		class EntityTypes;
	}
	namespace Graphics
	{
		class View;
		class Projection;
		enum ProjectionMode;
		class Shader;
		class VertexBuffer;
		class IndexBuffer;
		class FloatBuffer;
		class FrameBuffer;
		class UniformBuffer;
		class Texture;
		class Model;
		class Fermat;

		class Renderer
		{
		private:			
			View* view;
			Projection* projection;

			Skybox skybox;
			Maths::Vector4 clipPlane;
			
			//Manager Attributes
			Management::Manager ShaderManager;
			Management::Manager BufferManager;
			Management::Manager TextureManager;
			World::TerrainManager* terrainManager;			
			World::EntityTypes* entityTypes;
			IDisposable* mPointer;

			//Renderable Attributes
			std::map<Fermat, std::vector<World::Entity*>> entities;
			std::vector<World::Light*> lights;
			World::Landscape* world;		

			//Batch Rendering			
			void RenderSkybox();
			void RenderEntities();
			void RenderTerrain();
			void RenderWater(FrameBuffer*, FrameBuffer*);
			void RenderEffectBloom(FrameBuffer*, FloatBuffer*);
			void RenderEffectGaussian(FrameBuffer*, FloatBuffer*, Maths::Vector2);
			void RenderEffectMixture(FrameBuffer*, FrameBuffer*, FrameBuffer*, FloatBuffer*, float, float);
			void RenderWaterHelper(FrameBuffer*);
			void RenderWorldHelper(FrameBuffer*);

			//Private Initialization
			void LoadTextures(std::vector<std::string>, std::vector<std::string>);
			void LoadModels(std::vector<std::string>);
			void LoadShaders();
			void LoadUniformBuffers();
			void LoadWaterBuffers(int, int);
			void LoadFrameEffects(int, int);

			//Private Data Handling Methods
			void Clear();
			void Enable();
			void ViewUniform();
			void SkyUniform();
			void LightUniform();
			void Empty();
			void Dispose();

		public:
			//Constructors
			Renderer();
			Renderer(View*, Projection*);
			Renderer(Maths::Vector3, Maths::Vector3, ProjectionMode, float, float, float, float);
			~Renderer();

			//Initialize Methods
			void Init(int, int);
			void Resize(int, int);

			//Dynamic Casters
			Shader* GetShader(std::string);
			VertexBuffer* GetVertexBuffer(std::string);
			IndexBuffer* GetIndexBuffer(std::string);
			Texture* GetTexture(std::string);
			FloatBuffer* GetFloatBuffer(std::string);
			FrameBuffer* GetFrameBuffer(std::string);
			UniformBuffer* GetUniformBuffer(std::string);

			//Process Methods
			void Process(World::Entity*);
			void Process(World::Light*);
			void Process(World::Landscape*);
			void Process(std::vector<World::Entity*>);
			void Process(std::vector<World::Light*>);

			//Data Handling Methods
			void Render();			

			//Getter/Setter Methods
			void SetView(View*);
			void SetProjection(Projection*);
			void SetTerrainManager(World::TerrainManager*);
			void SetEntityTypes(World::EntityTypes*);
			View* GetView();
			Projection* GetProjection();

			//Register Methods
			void Register(std::string, Shader*);
			void Register(std::string, VertexBuffer*);
			void Register(std::string, IndexBuffer*);
			void Register(std::string, Model*);
			void Register(std::string, Texture*);
		};
	}
}
