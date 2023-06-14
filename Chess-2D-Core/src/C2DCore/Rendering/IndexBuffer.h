#pragma once
#include "C2DCore.h"
#include "IRenderPart.h"

namespace C2DCore
{
	class IndexBuffer : public IRenderPart
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(const unsigned int* data, unsigned int count);
		virtual ~IndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		void OnDestroy() const override;

		inline unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}