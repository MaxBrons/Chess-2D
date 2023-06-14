#pragma once
#include "C2DCore.h"

/// <summary>
/// This file is copied from TheCherno.
/// Source: https://github.com/TheCherno/OpenGL/blob/master/OpenGL-Core/src/GLCore/Util/Shader.h
/// </summary>

namespace C2DCore
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader();
		GLuint GetRendererID() { return m_RendererID; }

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform4f(const std::string& name, float r, float g, float b, float a);
		void SetUniform4f(const std::string& name, const glm::mat4 matrix);

		static Shader* FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		static Shader* FromGLSLSource(const std::string& vertexSource, const std::string& fragmentSource);

	private:
		void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void LoadShader(const std::string& vertSource, const std::string& fragSource);
		GLuint CompileShader(GLenum type, const std::string& source);

		int GetUniformLocation(const std::string& name);

	private:
		GLuint m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
