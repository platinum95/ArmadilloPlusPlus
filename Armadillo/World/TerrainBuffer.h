#pragma once
#include "../Graphics/VertexBuffer.h"
#include <vector>

namespace Armadillo
{
	namespace World 
	{
		class TerrainData;

		class TerrainBuffer : public Graphics::VertexBuffer
		{
		private:
			TerrainData* tennant;
		public:		

			TerrainBuffer(std::vector<float>&);

			bool IsOccupied();
			void BufferData(TerrainData*);
			void BufferData();
			void Evict();
			bool IsTennant(TerrainData*);
		};
	}
}