#include "c2dpch.h"
#include "GameBehaviour.h"

namespace C2DGame
{
	void GameBehaviour::OnStart()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		auto ortho = glm::ortho(-(16.0f / 9.0f), (16.0f / 9.0f), -1.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 transform = glm::inverse(glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1)));
		m_VPM = ortho * transform;

		m_Shader_Frag =
			"#version 450 core						\n\
			layout(location = 0) out vec4 o_Color;	\n\
			uniform vec4 u_Color;					\n\
													\n\
			void main()								\n\
			{										\n\
				o_Color = u_Color;					\n\
			}";

		m_Shader_Vert =
			"#version 450 core						\n\
			layout(location = 0) in vec3 a_Position	\n\
			uniform mat4 u_ViewProjection;			\n\
													\n\
			void main()								\n\
			{										\n\
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);\n\
			}";

		glCreateVertexArrays(1, &m_QuadVA);
		glBindVertexArray(m_QuadVA);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		glCreateBuffers(1, &m_QuadVB);
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		glCreateBuffers(1, &m_QuadIB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void GameBehaviour::OnUpdate(float deltaTime)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		GLuint program = LoadShader(m_Shader_Vert, m_Shader_Frag);
		glUseProgram(program);

		int location = glGetUniformLocation(program, "u_ViewProjection");

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_VPM));

		location = glGetUniformLocation(program, "u_Color");
		glUniform4fv(location, 1, glm::value_ptr(m_SquareColor));

		glBindVertexArray(m_QuadVA);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void GameBehaviour::OnDestroy()
	{
		glDeleteVertexArrays(1, &m_QuadVA);
		glDeleteBuffers(1, &m_QuadVB);
		glDeleteBuffers(1, &m_QuadIB);
	}

	void GameBehaviour::OnEvent(Event& e)
	{
		if (e.GetEventType() == MouseButtonPressedEvent::GetStaticEventType())
			m_SquareColor = m_SquareAlternateColor;
		if (e.GetEventType() == MouseButtonReleasedEvent::GetStaticEventType())
			m_SquareColor = m_SquareBaseColor;
	}

	GLuint GameBehaviour::CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);
		}

		return shader;
	}

	GLuint GameBehaviour::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::string vertexSource = vertexShaderPath;
		std::string fragmentSource = fragmentShaderPath;

		GLuint program = glCreateProgram();
		int glShaderIDIndex = 0;

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}
}
