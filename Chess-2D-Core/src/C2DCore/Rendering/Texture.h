#pragma once
#include "C2DCore.h"
#include "stb_image/stb_image.h"

#include <glfw/glfw3.h>

namespace C2DCore
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& path);
		virtual ~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		int m_Width;
		int m_Height;
		int m_BitsPerPixel;
	};
}
