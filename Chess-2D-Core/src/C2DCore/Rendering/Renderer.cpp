#include "c2dpch.h"
#include "Renderer.h"

namespace C2DCore
{
	void Renderer::Clear() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		va.Bind();
		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}