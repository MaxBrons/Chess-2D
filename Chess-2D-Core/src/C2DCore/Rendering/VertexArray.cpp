#include "c2dpch.h"
#include "VertexArray.h"

namespace C2DCore
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::AddBuffer(const VertexBufferLayout& layout)
	{
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, layout.GetStride(), (const void*)offset);

			offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::OnDestroy() const
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
}
