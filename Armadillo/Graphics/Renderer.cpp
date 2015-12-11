#include "Renderer.h"

#include "Colour.h"
#include "ShaderLoader.h"
#include "ShaderFactory.h"
#include "FrameEffect.h"
#include "View.h"
#include "Projection.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "FloatBuffer.h"
#include "FrameBuffer.h"
#include "UniformBuffer.h"
#include "Texture.h"

#include "../World/Terrain.h"
#include "../World/Entity.h"
#include "../World/Light.h"
#include "../World/Landscape.h"
#include "../World/Water.h"
#include "../World/TerrainManager.h"
#include "../World/TerrainBuffer.h"
#include "../World/EntityTypes.h"
#include "../Management/Logger.h"
#include "../Osiris.h"

#include <GL\glew.h>
#include <fstream>
#include <sstream>

namespace Armadillo
{
	namespace Graphics
	{
		using namespace Management;
		using namespace World;
		using namespace Colour;
		using namespace Maths;
		using namespace std;

#pragma region Constructors
		Renderer::Renderer()
		{
			this->ShaderManager = Manager("ShaderManager");
			this->BufferManager = Manager("BufferManager");
			this->TextureManager = Manager("TextureManager");
			this->terrainManager = NULL;
			this->mPointer = NULL;
			this->entityTypes = NULL;
			this->skybox = Skybox(DarkCyan, 0.001f, 1.0f);
			this->entities = map<Fermat, vector<Entity*>>();
			this->lights = vector<Light*>();
		}

		Renderer::Renderer(View* v, Projection* p) : Renderer()
		{
			this->view = v;
			this->projection = p;
		}

		Renderer::Renderer(Vector3 p, Vector3 r, ProjectionMode m, float fov, float a, float n, float f) : Renderer()
		{
			this->view = new View(p, r);
			this->projection = new Projection(m, fov, a, n, f);
		}

		Renderer::~Renderer()
		{
			delete this->mPointer;
		}
#pragma endregion	

#pragma region Initialization
		void Renderer::LoadTextures(vector<string> textures, vector<string> skybox)
		{
			for (string s : textures)
			{
				this->Register(s, Texture::LoadTexture(Osiris::PathTextures + s + Osiris::ExtensionImage));
			}
			for (int i = 0; i < skybox.size(); i++)
			{
				skybox[i] = Osiris::PathTextures + skybox[i] + Osiris::ExtensionImage;
			}
			this->Register("Skybox", Texture::LoadCubeTexture(skybox));
			this->BufferManager.Register(Osiris::FloatBufferSkybox, Skybox::CubeBuffer());
		}

		void Renderer::LoadModels(vector<string> models)
		{
			Model* model;
			for (string s : models)
			{
				model = Model::LoadObject(Osiris::PathModels + s + Osiris::ExtensionModel);

				this->Register(s + "V", new VertexBuffer(model, GL_STATIC_DRAW));
				this->Register(s + "I", new IndexBuffer(model, GL_STATIC_DRAW, GL_UNSIGNED_INT));
			}
		}

		void Renderer::LoadShaders()
		{
			ShaderFactory sFactory = ShaderFactory();
			this->Register(Osiris::ShaderEntity,
				sFactory.Load(Osiris::ShaderEntityVertex, Osiris::ShaderEntityFragment)->
				RegisterAttribute("vPosition")->
				RegisterAttribute("vNormal")->
				RegisterAttribute("vTextureCoords")->				
				RegisterUniform("mModelMatrix")->
				RegisterUniform("vLightPosition")->
				RegisterUniform("vTextureData")->
				RegisterUniform("uTexture")->
				RegisterUniform("vLightColour")->
				RegisterUniform("fShineDamper")->
				RegisterUniform("fReflectivity")->
				Compile());
			this->Register(Osiris::ShaderTerrain,
				sFactory.Load(Osiris::ShaderTerrainVertex, Osiris::ShaderTerrainFragment)->
				RegisterAttribute("vPosition")->
				RegisterAttribute("fHeight")->
				RegisterAttribute("vNormal")->
				RegisterUniform("mModelMatrix")->
				RegisterUniform("vLightPosition")->
				RegisterUniform("vLightColour")->
				Compile());
			this->Register(Osiris::ShaderWater,
				sFactory.Load(Osiris::ShaderWaterVertex, Osiris::ShaderWaterFragment)->
				RegisterAttribute("vPosition")->
				RegisterUniform("mModelMatrix")->
				RegisterTexture("uReflectionTexture", 0)->
				RegisterTexture("uRefractionTexture", 1)->
				RegisterTexture("uDuDvTexture", 2)->
				RegisterTexture("uNormalTexture", 3)->
				RegisterTexture("uDepthTexture", 4)->
				RegisterUniform("fDuDvOffset")->
				RegisterUniform("vLightPosition")->
				RegisterUniform("vLightColour")->
				RegisterUniform("fNearPlane")->
				RegisterUniform("fFarPlane")->
				RegisterUniform("vWaterColour")->
				Compile());
			this->Register(Osiris::ShaderSkybox,
				sFactory.Load(Osiris::ShaderSkyboxVertex, Osiris::ShaderSkyboxFragment)->
				RegisterAttribute("vPosition")->
				RegisterUniform("vSkyColour")->
				RegisterTexture("uCubeMap", 0)->
				Compile());
			this->Register(Osiris::ShaderBloom,
				sFactory.Load(Osiris::ShaderBloomVertex, Osiris::ShaderBloomFragment)->
				RegisterAttribute("vPosition")->
				RegisterTexture("uFrameTexture", 0)->
				Compile());
			this->Register(Osiris::ShaderGaussian,
				sFactory.Load(Osiris::ShaderGaussianVertex, Osiris::ShaderGaussianFragment)->
				RegisterAttribute("vPosition")->
				RegisterUniform("vDirection")->
				RegisterUniform("fBlur")->
				RegisterTexture("uFrameTexture", 0)->
				Compile());
			this->Register(Osiris::ShaderMixture,
				sFactory.Load(Osiris::ShaderMixtureVertex, Osiris::ShaderMixtureFragment)->
				RegisterAttribute("vPosition")->
				RegisterUniform("fMix1")->
				RegisterUniform("fMix2")->
				RegisterTexture("uTexture0", 0)->
				RegisterTexture("uTexture1", 1)->
				RegisterTexture("uTexture2", 2)->
				RegisterTexture("uDepthTexture0", 3)->
				Compile());
		}

		void Renderer::LoadUniformBuffers()
		{
			UniformBuffer* uBuffer = new UniformBuffer(Osiris::UniformBufferSkyFog, 0, 24);
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderEntity));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderWater));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderTerrain));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderSkybox));
			this->BufferManager.Register(Osiris::UniformBufferSkyFog, uBuffer);

			uBuffer = new UniformBuffer(Osiris::UniformBufferViewData, 1, 144);
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderEntity));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderWater));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderTerrain));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderSkybox));
			this->BufferManager.Register(Osiris::UniformBufferViewData, uBuffer);

			uBuffer = new UniformBuffer(Osiris::UniformBufferTerrainColours, 2, 208);
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderTerrain));
			uBuffer->AddData(Colour::Snow);
			uBuffer->AddData(Colour::Tundra);
			uBuffer->AddData(Colour::Bare);
			uBuffer->AddData(Colour::Scorched);
			uBuffer->AddData(Colour::Taiga);
			uBuffer->AddData(Colour::Shrubland);
			uBuffer->AddData(Colour::TemperateDesert);
			uBuffer->AddData(Colour::TemperateRainForest);
			uBuffer->AddData(Colour::TemperateDeciduousForest);
			uBuffer->AddData(Colour::Grassland);
			uBuffer->AddData(Colour::TropicalRainForest);
			uBuffer->AddData(Colour::TropicalSeasonalForest);
			uBuffer->AddData(Colour::SubtropicalDesert);
			uBuffer->BufferData();
			this->BufferManager.Register(Osiris::UniformBufferTerrainColours, uBuffer);

			uBuffer = new UniformBuffer(Osiris::UniformBufferTerrainSelectors, 3, 64);
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderTerrain));
			this->BufferManager.Register(Osiris::UniformBufferTerrainSelectors, uBuffer);

			uBuffer = new UniformBuffer(Osiris::UniformBufferLightData, 4, 48);
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderEntity));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderWater));
			uBuffer->BlockBindShader(this->GetShader(Osiris::ShaderTerrain));
			this->BufferManager.Register(Osiris::UniformBufferLightData, uBuffer);
		}

		void Renderer::LoadWaterBuffers(int Width, int Height)
		{
			this->BufferManager.Register(Osiris::FloatBufferWaterQuad, Water::QuadBuffer());
			this->BufferManager.Register(Osiris::FrameBufferReflection, Water::ReflectionBuffer(Width, Height));
			this->BufferManager.Register(Osiris::FrameBufferRefraction, Water::RefractionBuffer(Width, Height));
		}

		void Renderer::LoadFrameEffects(int Width, int Height)
		{
			this->BufferManager.Register(Osiris::FloatBufferFrameQuad, FrameEffect::GetScreenQuadBuffer());

			FrameBuffer* fBuffer = new FrameBuffer(Width, Height);
			fBuffer->AddTextureAttachment();
			fBuffer->Unbind();
			this->BufferManager.Register(Osiris::FrameBufferTexture0, fBuffer);

			fBuffer = new FrameBuffer(Width, Height);
			fBuffer->AddTextureAttachment();
			fBuffer->Unbind();
			this->BufferManager.Register(Osiris::FrameBufferTexture1, fBuffer);

			fBuffer = new FrameBuffer(Width, Height);
			fBuffer->AddTextureAttachment();
			fBuffer->Unbind();
			this->BufferManager.Register(Osiris::FrameBufferTexture2, fBuffer);

			fBuffer = new FrameBuffer(Width, Height);
			fBuffer->AddTextureAttachment();
			fBuffer->AddDepthTextureAttachment();
			//fBuffer->AddDepthBufferAttachment();
			fBuffer->Unbind();
			this->BufferManager.Register(Osiris::FrameBufferTextureDepth0, fBuffer);
		}

		void Renderer::Init(int Width, int Height)
		{
			vector<string> models = vector<string>();
			vector<string> textures = vector<string>();
			vector<string> skybox = vector<string>();
			ifstream stream(Osiris::FileResources);
			Logger::Log("Loading Resources...");
			string line = "";
			while (!stream.eof())
			{
				getline(stream, line);
				if (line[0] == 'm')
					models.push_back(line.substr(2, line.size() - 2));
				else if (line[0] == 't')
					textures.push_back(line.substr(2, line.size() - 2));
				else if (line[0] == 's')
					skybox.push_back(line.substr(2, line.size() - 2));
			}
			stream.close();

			this->LoadModels(models);
			this->LoadTextures(textures, skybox);
			this->LoadShaders();
			this->LoadUniformBuffers();
			this->LoadWaterBuffers(Width, Height);
			this->LoadFrameEffects(Width, Height);
		}

		void Renderer::Resize(int i, int j)
		{
			this->projection->ChangeAspectRatio(Osiris::DisplayAspectRatio);
		}
#pragma endregion

#pragma region Getters/Setters
		void Renderer::SetView(View* v)
		{
			this->view = v;
		}

		void Renderer::SetProjection(Projection* p)
		{
			this->projection = p;
		}

		void Renderer::SetTerrainManager(TerrainManager* tm)
		{
			this->terrainManager = tm;
		}

		void Renderer::SetEntityTypes(EntityTypes* et)
		{
			this->entityTypes = et;
		}

		View* Renderer::GetView()
		{
			return this->view;
		}

		Projection* Renderer::GetProjection()
		{
			return this->projection;
		}
#pragma endregion

#pragma region RenderHandling
		void Renderer::Clear()
		{
			glClearColor(this->skybox.SkyColour.x, this->skybox.SkyColour.y, this->skybox.SkyColour.z, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Renderer::Enable()
		{
			glEnable(GL_DEPTH_TEST);
			//glDepthFunc(GL_LESS);
			glEnable(GL_CULL_FACE);
			glEnable(GL_CLIP_DISTANCE0);
			glCullFace(GL_BACK);
		}

		void Renderer::Empty()
		{
			this->entities.clear();
			this->lights.clear();
		}
#pragma endregion 

#pragma region Process
		void Renderer::Process(World::Landscape* world)
		{
			this->Process(world->Lights);
			this->world = world;
		}

		void Renderer::Process(Entity* entity)
		{
			if (entity == NULL) return;

			Fermat fermat = entityTypes->GetType(entity->Type);

			if (this->entities.count(fermat) == 0)
			{
				vector<Entity*> vec = vector<Entity*>();
				vec.push_back(entity);
				this->entities[fermat] = vec;
			}
			else
			{
				this->entities[fermat].push_back(entity);
			}
		}

		void Renderer::Process(Light* light)
		{
			if (light == NULL) return;

			this->lights.push_back(light);
		}

		void Renderer::Process(vector<Entity*> entities)
		{
			for (Entity* e : entities)
			{
				this->Process(e);
			}
		}

		void Renderer::Process(vector<Light*> lights)
		{
			for (Light* l : lights)
			{
				this->Process(l);
			}
		}

#pragma endregion

#pragma region Render		
		void Renderer::SkyUniform()
		{
			UniformBuffer* uSkyFog = GetUniformBuffer(Osiris::UniformBufferSkyFog);
			uSkyFog->AddData(this->skybox.SkyColour);
			uSkyFog->AddData(this->skybox.Density);
			uSkyFog->AddData(this->skybox.Gradient);
			uSkyFog->BufferData();
		}

		void Renderer::ViewUniform()
		{
			UniformBuffer* uViewData = GetUniformBuffer(Osiris::UniformBufferViewData);

			uViewData->AddData(view->GetMatrix());
			uViewData->AddData(projection->GetMatrix());
			uViewData->AddData(view->Position);
			uViewData->BufferData();
		}

		void Renderer::LightUniform()
		{
			UniformBuffer* uLightData = GetUniformBuffer(Osiris::UniformBufferLightData);

			for (Light* l : this->lights)
			{
				l->Update();
				uLightData->AddData(l->Data(), LightDataSize);
			}
			uLightData->BufferData();
		}

		void Renderer::RenderSkybox()
		{
			FloatBuffer* fBuffer = GetFloatBuffer(Osiris::FloatBufferSkybox);
			Shader* shader = GetShader(Osiris::ShaderSkybox);
			Texture* texture = GetTexture("Skybox");
			shader->Start();
			fBuffer->Bind();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture->Id);

			ShaderLoader::LoadMatrix(shader, "mViewMatrix", view->GetMatrix());
			fBuffer->Render(Osiris::DrawType);

			texture->UnBind();
			fBuffer->Unbind();
			shader->Stop();
		}

		void Renderer::RenderWaterHelper(FrameBuffer* fFrameBuffer)
		{
			if (fFrameBuffer != NULL)
				fFrameBuffer->Bind();
			this->Clear();
			this->ViewUniform();
			this->RenderTerrain();
			this->RenderEntities();
			this->RenderSkybox();
			if (fFrameBuffer != NULL)
				fFrameBuffer->Unbind();
		}

		void Renderer::RenderWorldHelper(FrameBuffer* fFrameBuffer)
		{
			FrameBuffer* fReflectBuffer = GetFrameBuffer(Osiris::FrameBufferReflection);
			FrameBuffer* fRefractBuffer = GetFrameBuffer(Osiris::FrameBufferRefraction);

			float viewDistance = 2 * (view->Position.y - Osiris::WorldWaterHeight);

			//Reflection			
			this->view->Position.y -= viewDistance;
			this->view->Rotation.x = -this->view->Rotation.x;
			this->clipPlane = Vector4(0, 1, 0, -Osiris::WorldWaterHeight + 1);

			RenderWaterHelper(fReflectBuffer);

			//Refraction
			this->view->Position.y += viewDistance;
			this->view->Rotation.x = -this->view->Rotation.x;
			this->clipPlane = Vector4(0, -1, 0, Osiris::WorldWaterHeight);

			RenderWaterHelper(fRefractBuffer);

			glDisable(GL_CLIP_DISTANCE0);
			//this->clipPlane = Vector4(0, -1, 0, Osiris::WorldMaxHeight);

			//World
			if (fFrameBuffer != NULL)
				fFrameBuffer->Bind();
			this->Clear();
			this->ViewUniform();
			this->RenderEntities();
			this->RenderTerrain();
			this->RenderWater(fReflectBuffer, fRefractBuffer);
			this->RenderSkybox();
			if (fFrameBuffer != NULL)
				fFrameBuffer->Unbind();
		}

		void Renderer::Render()
		{
			this->Enable();
			this->LightUniform();
			this->SkyUniform();

			if (Osiris::PostEffectBloomEnable || Osiris::PostEffectFieldBlurEnable)
			{
				FrameBuffer* fFrameBufferTextureDepth0 = GetFrameBuffer(Osiris::FrameBufferTextureDepth0);
				FrameBuffer* fFrameBufferTexture0 = GetFrameBuffer(Osiris::FrameBufferTexture0);
				FrameBuffer* fFrameBufferTexture1 = GetFrameBuffer(Osiris::FrameBufferTexture1);
				FrameBuffer* fFrameBufferTexture2 = GetFrameBuffer(Osiris::FrameBufferTexture2);
				FloatBuffer* fFrameQuad = GetFloatBuffer(Osiris::FloatBufferFrameQuad);

				float mix1, mix2;
				mix1 = mix2 = 0;

				RenderWorldHelper(fFrameBufferTextureDepth0);

				if (Osiris::PostEffectBloomEnable)
				{
					fFrameBufferTexture0->Bind();
					this->Clear();
					this->RenderEffectBloom(fFrameBufferTextureDepth0, fFrameQuad);
					fFrameBufferTexture0->Unbind();

					fFrameBufferTexture1->Bind();
					this->Clear();
					this->RenderEffectGaussian(fFrameBufferTexture0, fFrameQuad, Vector2(1, 0));
					fFrameBufferTexture1->Unbind();

					fFrameBufferTexture0->Bind();
					this->Clear();
					this->RenderEffectGaussian(fFrameBufferTexture1, fFrameQuad, Vector2(0, 1));
					fFrameBufferTexture0->Unbind();
					mix1 = Osiris::PostEffectBloomMix;

					if (!Osiris::PostEffectFieldBlurEnable)
					{
						fFrameBufferTexture2->Bind();
						this->Clear();
						fFrameBufferTexture2->Unbind();
					}
				}
				if (Osiris::PostEffectFieldBlurEnable)
				{
					fFrameBufferTexture1->Bind();
					this->Clear();
					this->RenderEffectGaussian(fFrameBufferTextureDepth0, fFrameQuad, Vector2(1, 0));
					fFrameBufferTexture1->Unbind();

					fFrameBufferTexture2->Bind();
					this->Clear();
					this->RenderEffectGaussian(fFrameBufferTextureDepth0, fFrameQuad, Vector2(0, 1));
					fFrameBufferTexture2->Unbind();
					mix2 = Osiris::PostEffectFieldBlurMix;

					if (!Osiris::PostEffectBloomEnable)
					{
						fFrameBufferTexture0->Bind();
						this->Clear();
						fFrameBufferTexture0->Unbind();
					}
				}
				this->Clear();
				this->RenderEffectMixture(fFrameBufferTextureDepth0, fFrameBufferTexture0, fFrameBufferTexture2, fFrameQuad, mix1, mix2);
			}
			else
			{
				RenderWorldHelper(NULL);
			}
			this->Empty();
		}

		void Renderer::RenderEffectGaussian(FrameBuffer* fPreviousBuffer, FloatBuffer* fBuffer, Vector2 dir)
		{
			Shader* shader = GetShader(Osiris::ShaderGaussian);

			shader->Start();
			fBuffer->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fPreviousBuffer->Attachments[0]);
			if (dir.y == 1)
				ShaderLoader::LoadFloat(shader, "fResolution", fPreviousBuffer->Height);
			else
				ShaderLoader::LoadFloat(shader, "fResolution", fPreviousBuffer->Width);
			ShaderLoader::LoadVector(shader, "vDirection", dir);

			fBuffer->Render(GL_TRIANGLE_STRIP);

			glBindTexture(GL_TEXTURE_2D, 0);
			shader->Stop();
			fBuffer->Unbind();
		}

		void Renderer::RenderEffectBloom(FrameBuffer* fPreviousBuffer, FloatBuffer* fBuffer)
		{
			Shader* shader = GetShader(Osiris::ShaderBloom);

			shader->Start();
			fBuffer->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fPreviousBuffer->Attachments[0]);

			ShaderLoader::LoadFloat(shader, "fThreshold", Osiris::PostEffectBloomThreshold);

			fBuffer->Render(GL_TRIANGLE_STRIP);

			glBindTexture(GL_TEXTURE_2D, 0);
			shader->Stop();
			fBuffer->Unbind();
		}

		void Renderer::RenderEffectMixture(FrameBuffer* fBuffer0, FrameBuffer* fBuffer1, FrameBuffer* fBuffer2, FloatBuffer* fQuadBuffer, float mix1, float mix2)
		{
			Shader* shader = GetShader(Osiris::ShaderMixture);

			shader->Start();
			fQuadBuffer->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fBuffer0->Attachments[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, fBuffer1->Attachments[0]);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, fBuffer2->Attachments[0]);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, fBuffer0->Attachments[1]);

			ShaderLoader::LoadFloat(shader, "fMix1", mix1);
			ShaderLoader::LoadFloat(shader, "fMix2", mix2);

			fQuadBuffer->Render(GL_TRIANGLE_STRIP);

			glBindTexture(GL_TEXTURE_2D, 0);
			shader->Stop();
			fQuadBuffer->Unbind();
		}

		void Renderer::RenderWater(FrameBuffer* fReflectBuffer, FrameBuffer* fRefractBuffer)
		{
			FloatBuffer* fBuffer = GetFloatBuffer(Osiris::FloatBufferWaterQuad);
			Shader* shader = GetShader(Osiris::ShaderWater);
			Texture* texture = GetTexture("WaterDuDv");
			Texture* texture2 = GetTexture("WaterNormal");

			shader->Start();
			fBuffer->Bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fReflectBuffer->Attachments[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, fRefractBuffer->Attachments[0]);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture->Id);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture2->Id);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, fRefractBuffer->Attachments[1]);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_CULL_FACE);

			Osiris::WorldWaveDisplacement = (Osiris::WorldWaveDisplacement + 1) % 1000;
			ShaderLoader::LoadFloat(shader, "fDuDvOffset", (float)Osiris::WorldWaveDisplacement / 1000.0f);
			ShaderLoader::LoadFloat(shader, "fFarPlane", Osiris::DisplayFarPlane);
			ShaderLoader::LoadFloat(shader, "fNearPlane", Osiris::DisplayNearPlane);

			for (Water* w : this->terrainManager->GetWaters())
			{
				Matrix mModelMatrix = Matrix::Translation(w->Position) * Matrix::Scale(w->Scale);
				ShaderLoader::LoadMatrix(shader, "mModelMatrix", mModelMatrix);
				ShaderLoader::LoadVector(shader, "vWaterColour", w->Colour);
				fBuffer->Render(Osiris::DrawType);
			}

			glEnable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_BLEND);
			fBuffer->Unbind();
			shader->Stop();
		}

		void Renderer::RenderEntities()
		{
			if (this->entities.size() <= 0)
				return;

			Shader* shader = GetShader(Osiris::ShaderEntity);
			shader->Start();
			ShaderLoader::LoadVector(shader, "vClipPlane", this->clipPlane);
			for (map<Fermat, vector<Entity*>>::iterator iterator = entities.begin(); iterator != entities.end(); iterator++)
			{
				Fermat f = iterator->first;
				VertexBuffer* vBuffer = GetVertexBuffer(f.Buffer + "V");
				IndexBuffer* iBuffer = GetIndexBuffer(f.Buffer + "I");
				Texture* texture = GetTexture(f.Texture);

				texture->Bind();
				vBuffer->Bind();
				for (Entity* entity : iterator->second)
				{
					Matrix mModelMatrix = Matrix::ModelMatrix(entity->Position, entity->Rotation, entity->Scale);
					ShaderLoader::LoadMatrix(shader, "mModelMatrix", mModelMatrix);
					ShaderLoader::LoadVector(shader, "vTextureData", entity->TextureData);
					ShaderLoader::LoadFloat(shader, "fShineDamper", entity->ShineDamper);
					ShaderLoader::LoadFloat(shader, "fReflectivity", entity->Reflectivity);
					vBuffer->Render(Osiris::DrawType, *iBuffer);
				}
				vBuffer->Unbind();
				texture->UnBind();
			}
			shader->Stop();
		}

		void Renderer::RenderTerrain()
		{
			Shader* shader = GetShader(Osiris::ShaderTerrain);
			shader->Start();
			UniformBuffer* selector = GetUniformBuffer(Osiris::UniformBufferTerrainSelectors);

			ShaderLoader::LoadVector(shader, "vClipPlane", this->clipPlane);			

			for (Terrain* t : this->terrainManager->GetTerrains())
			{
				TerrainBuffer* vBuffer = t->GetTerrainBuffer();
				IndexBuffer* iBuffer = this->terrainManager->GetIndexBuffer(Osiris::DrawTerrainIndexBuffer);
		
				if (vBuffer == NULL || iBuffer == NULL || t == NULL)
					continue;

				selector->AddData(Vector3(0, 0, 0), (int)t->GetBiome().Type);
				selector->BufferData();

				vBuffer->Bind();
				ShaderLoader::LoadMatrix(shader, "mModelMatrix", Matrix::Translation(t->Position));
				vBuffer->Render(Osiris::DrawType, *iBuffer);

				vBuffer->Unbind();
			}
			shader->Stop();
		}
#pragma endregion

#pragma region ManagerGets
		Shader* Renderer::GetShader(string name)
		{
			this->mPointer = ShaderManager.Get(name);
			return dynamic_cast<Shader*>(mPointer);
		}

		VertexBuffer* Renderer::GetVertexBuffer(string name)
		{
			this->mPointer = BufferManager.Get(name);
			return dynamic_cast<VertexBuffer*>(mPointer);
		}

		FloatBuffer* Renderer::GetFloatBuffer(string name)
		{
			this->mPointer = BufferManager.Get(name);
			return dynamic_cast<FloatBuffer*>(mPointer);
		}

		IndexBuffer* Renderer::GetIndexBuffer(string name)
		{
			this->mPointer = BufferManager.Get(name);
			return dynamic_cast<IndexBuffer*>(mPointer);
		}

		Texture* Renderer::GetTexture(string name)
		{
			this->mPointer = TextureManager.Get(name);
			return dynamic_cast<Texture*>(mPointer);
		}

		FrameBuffer* Renderer::GetFrameBuffer(string name)
		{
			this->mPointer = BufferManager.Get(name);
			return dynamic_cast<FrameBuffer*>(mPointer);
		}

		UniformBuffer* Renderer::GetUniformBuffer(string name)
		{
			this->mPointer = BufferManager.Get(name);
			return dynamic_cast<UniformBuffer*>(mPointer);
		}
#pragma endregion

#pragma region Register

		void Renderer::Register(string name, Shader* shader)
		{
			this->ShaderManager.Register(name, shader);
		}

		void Renderer::Register(string name, VertexBuffer* buffer)
		{
			this->BufferManager.Register(name, buffer);
		}

		void Renderer::Register(string name, IndexBuffer* buffer)
		{
			this->BufferManager.Register(name, buffer);
		}

		void Renderer::Register(string name, Model* model)
		{
			this->Register(name + "V", new VertexBuffer(model, GL_STATIC_DRAW));
			this->Register(name + "I", new IndexBuffer(model, GL_STATIC_DRAW, GL_UNSIGNED_INT));
		}

		void Renderer::Register(string name, Texture* texture)
		{
			this->TextureManager.Register(name, texture);
		}
#pragma endregion
	}
}
