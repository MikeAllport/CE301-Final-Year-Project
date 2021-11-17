#pragma once
#include <App/Sprite.h>
#include <GE/Window.h>
#include <App/Game.h>
#include <App/Sprite.h>
#include <App/WorldGeneration/GeneratorSettings.h>

namespace GameEngineUnitTest
{
	class SpriteStub : public App::Sprite
	{
	public:
		SpriteStub( glm::vec3 size,
			App::GameObject* owner,
			App::TextureNameEnums e = App::TextureNameEnums::TEXT_ERROR) :
			App::Sprite(owner, App::TexturePacks::get(e)) {};
		glm::mat4 getModelMatrix() { return modelMatrix; }
		App::TexturePack getTexturePack() { return textPack; }
	};
	class GameObjectStub : public App::GameObject
	{
	public:
		GameObjectStub() :
			GameObject(glm::fvec3(0, 0, 0), glm::vec3(100, 100, 100)),
			sprite(glm::vec3(100,100,100), this, App::TextureNameEnums::TEXT_CHARACTER)
		{};
		SpriteStub sprite;
		bool getMoved() { return moved; }
	};

	class RendererStub : public GE::Graphics::RendererBatched
	{
	public:
		RendererStub() :
			RendererBatched("batchedRendererTest-vert.shader", "batchedRendererTest-frag.shader")
		{};
		bool modelBeenSet() { return modelSet; }
		void drawQuadTextured(std::shared_ptr<GE::Graphics::Texture>, 
			TexturePosition& pos = TexturePosition())
		{
			quadDrawn = true;
		}
		void operator=(const RendererStub& other) const {};
		bool quadDrawn = false;
	};
}