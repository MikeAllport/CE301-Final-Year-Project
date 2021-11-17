#pragma once

#include "ILayer.h"
#include "WorldLayer.h"
#include <App/WorldGeneration/World.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace App {
	class MenuLayer : public ILayer
	{
	public:
		MenuLayer(WorldLayer& world, Game& game) : world(world), game(game) {
			world.camHandler.get()->setZoom(1);
			initImgui();
			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
			world.camHandler.get()->setZoom(40);
		};

		~MenuLayer()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
		}

		// Inherited via ILayer
		virtual void onRender() override;

		virtual void onUpdate(const float& delta) override;

		virtual void onEvent(GE::Event& e) override;

		void onCreateWorld();
		void onFinalize();
		void initImgui();
		void renderHeatMap();

	private:
		WorldLayer& world;
		Game& game;
	};

}