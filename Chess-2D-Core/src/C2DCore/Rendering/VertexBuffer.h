#pragma once
#include "C2DCore.h"
#include "IRenderPart.h"

namespace C2DCore
{
	class VertexBuffer : public IRenderPart
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(const void* data, unsigned int size);
		virtual ~VertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void OnDestroy() const override;

	private:
		unsigned int m_RendererID;
	};
}