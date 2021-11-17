#include <gepch.h>
#include "MenuLayer.h"
#include <imgui/imgui_internal.h>

#pragma once

namespace App 
{
	void MenuLayer::onRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("World Generation");
		if (ImGui::CollapsingHeader("World Settings"))
		{
			ImGui::Columns(2, nullptr, false);
			ImGui::SetColumnOffset(1, 400);
			ImGui::PushItemWidth(150);
			ImGui::InputInt("Seed", &world.world.get()->SEED);
			ImGui::PushItemWidth(100);
			if (world.mapSettings.USE_PERLIN)
				ImGui::InputFloat("Noise Frequency", &world.mapSettings.FREQUENCY, 0, 0, 2);
			else
			{
				ImGui::InputFloat("Noise Roughness", &world.mapSettings.NOISE_ROUGHNESS, 0, 0, 2);
				ImGui::InputFloat("Noise Roughness divisor", &world.mapSettings.ROUGHNESS_DIV, 0, 0, 2);
			}
			ImGui::InputFloat("Noise Redistribution Factor", &world.mapSettings.REDIST_EXPON, 0, 0, 2);
			ImGui::InputFloat("Noise Symetry Factor", &world.mapSettings.SYMMETRY_FACTOR, 0, 0, 2);
			ImGui::InputFloat("Noise Distance factor", &world.mapSettings.DIST_FACT, 0, 0, 2);
			ImGui::InputFloat("Noise Distance amplitude", &world.mapSettings.DIST_EXPON, 0, 0, 2);
			ImGui::PopItemWidth();
			ImGui::NextColumn();
			ImGui::Checkbox("Noise Symmetry smoothing", &world.mapSettings.USE_SYMMETRY);
			if (!world.mapSettings.USE_PERLIN)
				ImGui::Checkbox("More Water", &world.mapSettings.USE_MORE_WATER);
			ImGui::Checkbox("Use distance function from center", &world.mapSettings.USE_DIST_RANGE);
			ImGui::Checkbox("Use distance amplitude", &world.mapSettings.USE_DIST_EXP);
			ImGui::Checkbox("Use new seed", &world.mapSettings.USE_RANDOM_SEED);
			ImGui::Checkbox("Use default settings", &world.mapSettings.USE_DEFAULTS);
			ImGui::Checkbox("Use pure noise", &world.mapSettings.USE_PURE_NOISE);
			ImGui::Checkbox("Use multi layered noise", &world.mapSettings.USE_MULTI_LAYERED);
			ImGui::EndColumns();
		}
		if (ImGui::CollapsingHeader("Object Settings"))
		{
			ImGui::InputInt("Minimum Distance", &world.objectSettings.minDist);
			world.objectSettings.minDist = std::max(70, world.objectSettings.minDist);
			ImGui::InputInt("Maximum Distance", &world.objectSettings.maxDist);
			world.objectSettings.maxDist = std::max(70, world.objectSettings.maxDist);
			ImGui::InputInt("Attempts to find point", &world.objectSettings.attempts);
			ImGui::InputInt("Blue Noise Radii", &world.objectSettings.blueNoise);
			ImGui::InputInt("Radius to draw", &world.objectSettings.cellRadius);
			ImGui::Checkbox("Use heatmap", &world.objectSettings.useHeatMap);
		}
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 400);
		ImGui::PushItemWidth(150);
		if (ImGui::Button("Generate World"))
		{
			onCreateWorld();
		}
		ImGui::NextColumn();
		if (ImGui::Button("Play"))
		{
			onFinalize();
		}
		if (world.objectSettings.useHeatMap)
		{
			renderHeatMap();
		}
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void MenuLayer::onUpdate(const float& delta)
	{
	}

	void MenuLayer::onEvent(GE::Event& e)
	{
		if (e.getType() == GE::EventType::MouseScrolled)
		{
			return;
		}
		e.setHandled();
	}

	void MenuLayer::renderHeatMap()
	{
		Tile::USE_GREYSCALE = true;
		world.renderer.get()->end();
		world.renderer.get()->begin();
		world.renderer.get()->projectionSet = true;
		world.renderer.get()->staticDrawn = true;
		for (int i = 0; i < world.WORLD_SIZE_WH + 1; ++i)
		{
			for (int j = 0; j < world.WORLD_SIZE_WH + 1; ++j)
			{
				int posX = j * Tile::TILE_WIDTH;
				int posY = i * Tile::TILE_WIDTH;
				Tile tile = world.world.get()->getTileFromXY(posX, posY);
				if (!tile.getSprite().isRenderable(*world.renderer.get()))
					continue;
				glm::fvec3 position(posX, 0, posY);
				PoissonGenerator& gen = world.objectGenerator.get()->poissonGen;
				Perlin& perlin = gen.perlin;
				float density = perlin.noiseWithFreq(posX, posY, world.objectSettings.blueNoise);
				tile.getSprite().setModelMatrix(*world.renderer.get());
				world.renderer.get()->drawQuadColored(glm::vec4(255, 0, 0, density / 1.5));
			}
		}
		world.renderer.get()->end();
	}

	void MenuLayer::onCreateWorld()
	{
		world.renderer->clearStaticQuads();
		GameObject::objectIDCount = 0;
		world.initWorld();
		world.initObjects();
	}

	void MenuLayer::onFinalize()
	{
		world.camHandler.get()->setZoom(1);
		isDead = true;
	}

	void MenuLayer::initImgui()
	{
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(game.getWindow().getGLFWWindow(), true);
	}
}