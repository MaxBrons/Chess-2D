#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace C2DCore
{
	class Renderer
	{
	public:
		void Clear() const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	};
}
