#include "EntityTree.h"

namespace Armadillo
{
	namespace World
	{
		EntityLeaf::EntityLeaf()
		{
			this->Parent = NULL;			
			this->Displacement = NULL;
			this->Rotation = NULL;
			this->Entity = NULL;
		}

		EntityTree::EntityTree()
		{
			this->Tree = std::vector<EntityLeaf*>();
		}

		void EntityTree::AddRoot(Entity* entity, Armadillo::Maths::Vector3* dis, Armadillo::Maths::Vector3* rot)
		{
			EntityLeaf* leaf = new EntityLeaf();
			leaf->Entity = entity;
			leaf->Displacement = dis;
			leaf->Rotation = rot;
			this->Tree.push_back(leaf);
		}

		void EntityTree::AddEntity(Entity* entity, int i)
		{
			EntityTree::AddEntity(entity, NULL, NULL, i);
		}

		void EntityTree::AddEntity(Entity* entity, Armadillo::Maths::Vector3* dis, Armadillo::Maths::Vector3* rot, int i)
		{
			if (this->Tree.size() > i)
			{
				EntityLeaf* leaf = new EntityLeaf();
				leaf->Entity = entity;			
				leaf->Parent = this->Tree[i];				
				leaf->Displacement = dis;
				leaf->Rotation = rot;
				this->Tree.push_back(leaf);
			}

		}

		void EntityTree::AddMatrix(Armadillo::Maths::Vector3* dis, Armadillo::Maths::Vector3* rot, int i)
		{
			if (this->Tree.size() > i)
			{
				this->Tree[i]->Displacement = dis;
				this->Tree[i]->Rotation = rot;
			}
		}

		Armadillo::Maths::Matrix EntityLeaf::GetMatrixProduct()
		{
			Armadillo::Maths::Matrix matrix = Armadillo::Maths::Matrix::Identity();
			EntityLeaf* curr = this;				
			while (curr != NULL)
			{			
				if (curr->Rotation != NULL)
					matrix = matrix * Armadillo::Maths::Matrix::Rotation(*curr->Rotation);
				if (curr->Displacement != NULL)
					matrix = matrix * Armadillo::Maths::Matrix::Translation(*curr->Displacement);			
			
				curr = curr->Parent;
			}				
			return matrix;
		}

		/*void Renderer::Render(Armadillo::World::EntityTree* entityTree, Armadillo::World::Light* light)
		{
			std::vector<Armadillo::World::EntityLeaf*>& tree = entityTree->Tree;
			for (Armadillo::World::EntityLeaf* leaf : tree)
			{
				Fermat& f = leaf->Entity->Fermat;
				VertexBuffer* vBuffer = GetVertexBuffer(f.Buffer + "V");
				IndexBuffer* iBuffer = GetIndexBuffer(f.Buffer + "I");
				Texture* texture = GetTexture(f.Texture);
				Shader* shader = GetShader(f.Shader);
				shader->Start();

				texture->Bind();
				vBuffer->Bind();

				Armadillo::World::Entity* entity = leaf->Entity;
				Armadillo::Maths::Matrix mModelMatrix = leaf->GetMatrixProduct() * Armadillo::Maths::Matrix::ModelMatrix(entity->Position, entity->Rotation, entity->Scale);
				ShaderLoader::LoadMatrix(shader, "mModelMatrix", mModelMatrix);
				ShaderLoader::LoadMatrix(shader, "mViewMatrix", view->GetMatrix());
				ShaderLoader::LoadMatrix(shader, "mProjectionMatrix", projection->GetMatrix());
				ShaderLoader::LoadVector(shader, "vLightPosition", light->Position);
				ShaderLoader::LoadVector(shader, "vLightColour", light->Colour);
				ShaderLoader::LoadVector(shader, "vTextureData", entity->TextureData);
				ShaderLoader::LoadFloat(shader, "fShineDamper", entity->ShineDamper);
				ShaderLoader::LoadFloat(shader, "fReflectivity", entity->Reflectivity);
				ShaderLoader::LoadVector(shader, "vSkyColour", this->skyColour);
				vBuffer->Render(GL_TRIANGLES, *iBuffer);

				vBuffer->Unbind();
				texture->UnBind();
				shader->Stop();
			}
		}*/
	}
}