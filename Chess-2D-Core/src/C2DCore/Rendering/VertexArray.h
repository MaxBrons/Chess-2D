#pragma once
#include "VertexBufferLayout.h"
#include "IRenderPart.h"

namespace C2DCore
{
	class VertexArray : public IRenderPart
	{
	public:
		VertexArray();
		virtual ~VertexArray();

		void AddBuffer(const VertexBufferLayout& layout);

		void Bind() const override;
		void Unbind() const override;
		void OnDestroy() const override;

	private:
		unsigned int m_RendererID;
	};
}