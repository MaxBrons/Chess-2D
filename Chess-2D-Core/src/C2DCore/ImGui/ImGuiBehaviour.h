#pragma once
#include "../Core/Behaviour.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace C2DCore
{
	class ImGuiBehaviour : public Behaviour
	{
	public:
		ImGuiBehaviour()
			:Behaviour("")
		{
		}
		~ImGuiBehaviour() = default;

		virtual void OnStart() override;
		virtual void OnDestroy() override;

		void Begin();
		void End();
	};
}
