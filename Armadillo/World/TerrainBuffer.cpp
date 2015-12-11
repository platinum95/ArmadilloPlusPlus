#include "TerrainBuffer.h"
#include "TerrainData.h"
#include <GL\glew.h>

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Graphics;
		using namespace std;

		TerrainBuffer::TerrainBuffer(std::vector<float>& f) : VertexBuffer()
		{
			VertexBuffer::GenBuffers(4);
			VertexBuffer::BufferData(0, 2, f.data(), f.size() / 2, GL_STATIC_DRAW);
		}

		bool TerrainBuffer::IsOccupied()
		{
			return this->tennant != NULL;
		}

		void TerrainBuffer::BufferData(TerrainData* t)
		{
			if (this->tennant == NULL)
			{
				this->tennant = t;
				VertexBuffer::BufferData(1, 1, this->tennant->GetHeights().data(), this->tennant->LengthSquared, GL_DYNAMIC_DRAW);
				VertexBuffer::BufferData(2, 3, this->tennant->GetNormals().data(), this->tennant->LengthSquared, GL_DYNAMIC_DRAW);
			}			
		}

		void TerrainBuffer::BufferData()
		{
			if (this->tennant != NULL)
			{				
				VertexBuffer::BufferData(1, 1, this->tennant->GetHeights().data(), this->tennant->LengthSquared, GL_DYNAMIC_DRAW);
				VertexBuffer::BufferData(2, 3, this->tennant->GetNormals().data(), this->tennant->LengthSquared, GL_DYNAMIC_DRAW);
			}
		}

		void TerrainBuffer::Evict()
		{
			this->tennant = NULL;
		}

		bool TerrainBuffer::IsTennant(TerrainData* td)
		{
			return this->tennant == td;
		}
	}
}