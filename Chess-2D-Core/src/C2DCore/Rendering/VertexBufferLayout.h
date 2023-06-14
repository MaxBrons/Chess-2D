#pragma once
#include "C2DCore.h"

namespace C2DCore
{
	struct VertexBufferElement
	{
	public:
		unsigned int Count;
		unsigned int Type;
		bool Normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}

		VertexBufferElement(const unsigned int Count, const unsigned int Type, bool Normalized)
			: Count(Count), Type(Type), Normalized(Normalized)
		{
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout();
		virtual ~VertexBufferLayout();

		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back(VertexBufferElement(count, GL_FLOAT, GL_FALSE ));
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back(VertexBufferElement(count, GL_UNSIGNED_INT, GL_FALSE ));
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back(VertexBufferElement(count, GL_UNSIGNED_BYTE, GL_TRUE ));
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
}
