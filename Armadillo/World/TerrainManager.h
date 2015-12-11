#pragma once
#include <vector>
#include <map>
#include "TerrainFactory.h"
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		class View;
		class IndexBuffer;
	}
	namespace World
	{		
		class Water;
		class Terrain;
		class TerrainData;
		class TerrainBuffer;
		class Seed;

		class TerrainManager
		{
		private:
			//Private Buffer Storage
			std::vector<Graphics::IndexBuffer*> indexBuffers;
			std::vector<TerrainData*> terrainDatas;
			std::vector<TerrainBuffer*> terrainBuffers;
			std::vector<Terrain*> terrains;
			std::vector<Water*> waters;			
			
			Maths::Vector2i cornerPoint;
			Maths::Vector2i lastCornerPoint;

			//Private World Infomation
			Graphics::View* view;
			TerrainFactory tFactory;
			Seed* seed;

			//Private Default Data			
			std::vector<float> fPositions;

			//Private Attributes
			float Size;
			int Width;
			int WidthSquared;

			//Private Initialization
			void Init();
			void InitIndexBuffers();
			void InitDefaultData();
			void InitPoints();
			void InitWater();
			void InitTerrain();
			void InitTerrainBuffers();

			//Private Testing Methods			
			bool RequireGenerate();

			Maths::Vector2 GetCentrePoint(Maths::Vector2i, int);
			Maths::Vector2 GetMidPoint(Maths::Vector2, Maths::Vector2);

			//Private Generate Methods;
			void GenerateIndexBuffer(int);			

			//Private Data Sorting Methods
			TerrainData* SearchStoredData(int, int);
			
			//Private Helper Methods
			void StitchData();
			int Index(int, int);
			bool InRange(int, int);
						
		public:
			//Constructors
			TerrainManager();
			TerrainManager(Seed*, Graphics::View*);

			//Public Generate Methods
			void Generate();

			//Public Accessors
			Graphics::IndexBuffer* GetIndexBuffer(int);
			std::vector<TerrainBuffer*>& GetTerrainBuffers();
			std::vector<Water*>& GetWaters();
			std::vector<Terrain*>& GetTerrains();
			float GetHeight(float, float);
			Terrain* GetTerrain(float, float);
		};
	}
}