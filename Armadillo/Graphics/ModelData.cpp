#include "ModelData.h"
#include "../Management/Logger.h"
#include <fstream>

namespace Armadillo
{
	namespace Graphics
	{
		std::vector<std::string> Split(std::string s, std::string t)
		{
			std::vector<std::string> res;
			while (1)
			{
				int pos = s.find(t);
				if (pos == -1){ res.push_back(s); break; }
				res.push_back(s.substr(0, pos));
				s = s.substr(pos + 1, s.size() - pos - 1);
			}
			return res;
		}

		Vertex::Vertex(int i, Armadillo::Maths::Vector3* p)
		{
			this->index = i;
			this->position = p;
			this->length = Armadillo::Maths::Vector3::Length(*p);
			this->duplicateVertex = NULL;
			this->textureIndex = NoIndex;
			this->normalIndex = NoIndex;
			this->hasDuplicate = false;
		}
		
		Vertex::~Vertex()
		{
			
		}
		
		int Vertex::Index()
		{
			return this->index;
		}
		
		float Vertex::Length()
		{
			return this->length;
		}
		
		bool Vertex::IsSet()
		{
			return this->textureIndex != NoIndex && this->normalIndex != NoIndex;
		}
		
		bool Vertex::HasSameTextureAndNormal(int i, int j)
		{
			return this->textureIndex == i && this->normalIndex == j;
		}
		
		void Vertex::SetTextureIndex(int i)
		{
			this->textureIndex = i;
		}
		
		void Vertex::SetNormalIndex(int i)
		{
			this->normalIndex = i;
		}
		
		Armadillo::Maths::Vector3* Vertex::Position()
		{
			return this->position;
		}
		
		int Vertex::TextureIndex()
		{
			return this->textureIndex;
		}
		
		int Vertex::NormalIndex()
		{
			return this->normalIndex;			
		}
		
		Vertex* Vertex::GetDuplicateVertex()
		{
			if (!this->HasDuplicate())
				return NULL;
			return this->duplicateVertex;
		}

		bool Vertex::HasDuplicate()
		{
			return this->hasDuplicate;
		}
		
		void Vertex::SetDuplicateVertex(Vertex* v)
		{			
			if (v != NULL)
			{
				this->duplicateVertex = v;
				this->hasDuplicate = true;
			}
		}
		
		Model::Model(float* v, float* t, float* n, int* i, float f, int l, int k)
		{
			this->Positions = v;
			this->TextureCoords = t;
			this->Normals = n;
			this->Indices = i;
			this->FurthestPoint = f;
			this->LengthIndex = l;
			this->LengthData = k;
		}
		
		Model::~Model()
		{
			delete[] this->Positions;
			delete[] this->TextureCoords;
			delete[] this->Normals;
			delete[] this->Indices;
		}		
		
		
		Model* Model::LoadObject(std::string s)
		{
			std::ifstream stream (s);
			std::string line = "";
			std::vector<Vertex> vertices = std::vector<Vertex>();
			std::vector<Armadillo::Maths::Vector2> textures = std::vector<Armadillo::Maths::Vector2>();
			std::vector<Armadillo::Maths::Vector3> normals = std::vector<Armadillo::Maths::Vector3>();
			std::vector<int> indices = std::vector<int>();
			
			while(true)
			{
				getline(stream, line);
				if(line[0] == 'v' && line[1] == ' ')
				{
					std::vector<std::string> currentLine = Split(line, " ");
					Armadillo::Maths::Vector3* vertex = new Armadillo::Maths::Vector3(
						std::stof(currentLine[1]),
						std::stof(currentLine[2]),
						std::stof(currentLine[3])
					);
					vertices.push_back(Vertex((int) vertices.size(), vertex));					
				}
				else if(line[0] == 'v' && line[1] == 't')
				{
					std::vector<std::string> currentLine = Split(line, " ");
					Armadillo::Maths::Vector2 tex = Armadillo::Maths::Vector2(
						std::stof(currentLine[1]),
						std::stof(currentLine[2])
					);
					textures.push_back(tex);
				}
				else if(line[0] == 'v' && line[1] == 'n')
				{
					std::vector<std::string> currentLine = Split(line, " ");
					Armadillo::Maths::Vector3 normal = Armadillo::Maths::Vector3(
						std::stof(currentLine[1]),
						std::stof(currentLine[2]),
						std::stof(currentLine[3])
					);
					normals.push_back(normal);
				}
				else if(line[0] == 'f' && line[1] == ' ')
				{
					break;
				}
			}
			do 
			{		
				if (!(line[0] == 'f' && line[1] == ' '))
					continue;

				std::vector<std::string> currentLine = Split(line, " ");
				std::vector<std::string> vertex1 = Split(currentLine[1], "/");
				std::vector<std::string> vertex2 = Split(currentLine[2], "/");
				std::vector<std::string> vertex3 = Split(currentLine[3], "/");
				ProcessVertex(vertex1, vertices, indices);
				ProcessVertex(vertex2, vertices, indices);
				ProcessVertex(vertex3, vertices, indices);			
			} while (getline(stream, line));
			stream.close();
			RemoveUnusedVertices(vertices);
			float* verticesArray = new float[vertices.size() * 3];
			float* texturesArray = new float[vertices.size() * 2];
			float* normalsArray = new float[vertices.size() * 3];
			float furthest = ConvertDataToArrays(vertices, textures, normals, verticesArray, texturesArray, normalsArray);
			int* indicesArray = ConvertIndicesToArray(indices);
			Model* data = new Model(verticesArray, texturesArray, normalsArray, indicesArray, furthest, indices.size(), vertices.size());
			return data;
		}
		
		void Model::ProcessVertex(std::vector<std::string>& vertex, std::vector<Vertex>& vertices, std::vector<int>& indices)
		{			
			int index = std::stoi(vertex[0]) - 1;
			Vertex* currentVertex = &vertices[index];
			int textureIndex = std::stoi(vertex[1]) - 1;
			int normalIndex = std::stoi(vertex[2]) - 1;

			if (textureIndex == -1 || normalIndex == -1)
			{
				Armadillo::Management::Logger::Print("Setting -1 Indices!");
			}

			if (!currentVertex->IsSet())
			{
				currentVertex->SetTextureIndex(textureIndex);
				currentVertex->SetNormalIndex(normalIndex);
				indices.push_back(index);
			}
			else
			{
				DealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
			}
		}
		
		void Model::DealWithAlreadyProcessedVertex(Vertex* previous, int tId, int nId, std::vector<int>& indices, std::vector<Vertex>& vertices)
		{
			if (previous->HasSameTextureAndNormal(tId, nId))
				indices.push_back(previous->Index());
			else
			{	
				Vertex* v = previous->GetDuplicateVertex();
				if (v != NULL)
					DealWithAlreadyProcessedVertex(v, tId, nId, indices, vertices);				
				else
				{
					Vertex* duplicate = new Vertex(vertices.size(), previous->Position());
					duplicate->SetTextureIndex(tId);
					duplicate->SetNormalIndex(nId);
					previous->SetDuplicateVertex(duplicate);
					vertices.push_back(*duplicate);
					indices.push_back(duplicate->Index());
				}
			}
		}

		void Model::RemoveUnusedVertices(std::vector<Vertex> vertices)
		{
			for (Vertex v : vertices)
			{
				if (!v.IsSet())
				{
					v.SetTextureIndex(0);
					v.SetNormalIndex(0);
				}
			}
		}

		float Model::ConvertDataToArrays(std::vector<Vertex> vertices, std::vector<Armadillo::Maths::Vector2> textures, std::vector<Armadillo::Maths::Vector3> normals, float verticesArray[], float texturesArray[], float normalsArray[])
		{
			float furthestPoint = 0;
			int size = vertices.size();
			for (int i = 0; i < size; i++)
			{
				Vertex& current = vertices[i];
				if (current.Length() > furthestPoint)
					furthestPoint = current.Length();
				int tId = current.TextureIndex();
				int nId = current.NormalIndex();

				Armadillo::Maths::Vector3* position = current.Position();
				Armadillo::Maths::Vector2* texture = &textures[tId];
				Armadillo::Maths::Vector3* normal = &normals[nId];
				verticesArray[i * 3] = position->x;
				verticesArray[i * 3 + 1] = position->y;
				verticesArray[i * 3 + 2] = position->z;
				texturesArray[i * 2] = texture->x;
				texturesArray[i * 2 + 1] = texture->y;
				normalsArray[i * 3] = normal->x;
				normalsArray[i * 3 + 1] = normal->y;
				normalsArray[i * 3 + 2] = normal->z;
			}
			return furthestPoint;
		}

		int* Model::ConvertIndicesToArray(std::vector<int> indices)
		{
			int size = indices.size();
			int* indicesArray = new int[size];
			for (int i = 0; i < size; i++)
				indicesArray[i] = indices[i];
			return indicesArray;
		}
	}
}