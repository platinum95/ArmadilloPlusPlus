#pragma once
#include "../Maths/VectorMath.h"
#include <string>
#include <vector>

namespace Armadillo
{
	namespace Graphics
	{
		struct Vertex
		{
		private:
			static const int NoIndex = -1;
			
			Armadillo::Maths::Vector3* position;
			int textureIndex;
			int normalIndex;
			Vertex* duplicateVertex;
			bool hasDuplicate;
			int index;
			float length;
		public:
			Vertex(int, Armadillo::Maths::Vector3*);
			~Vertex();
			
			int Index();
			float Length();
			bool IsSet();
			bool HasSameTextureAndNormal(int, int);
			bool HasDuplicate();
			void SetTextureIndex(int);
			void SetNormalIndex(int);
			Armadillo::Maths::Vector3* Position();
			int TextureIndex();
			int NormalIndex();
			Vertex* GetDuplicateVertex();
			void SetDuplicateVertex(Vertex*);		
		};
		
		class Model
		{
		private:
			static void ProcessVertex(std::vector<std::string>&, std::vector<Vertex>&, std::vector<int>&);
			static void DealWithAlreadyProcessedVertex(Vertex*, int, int, std::vector<int>&, std::vector<Vertex>&);
			static void RemoveUnusedVertices(std::vector<Vertex>);
			static float ConvertDataToArrays(std::vector<Vertex>, std::vector<Armadillo::Maths::Vector2>, std::vector<Armadillo::Maths::Vector3>, float*, float*, float*);
			static int* ConvertIndicesToArray(std::vector<int>);
		public:
			Model(float[], float[], float[], int[], float, int, int);
			~Model();

			int LengthIndex;
			int LengthData;
			
			float* Positions;
			float* TextureCoords;
			float* Normals;
			int* Indices;
			float FurthestPoint;
			
			static Model* LoadObject(std::string);
		};
	}
}