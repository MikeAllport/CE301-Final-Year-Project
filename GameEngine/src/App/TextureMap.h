#pragma once
#include <gepch.h>
#include <GE/Graphics/TextureCache.h>

namespace App
{
	enum TextureNameEnums
	{
		TEXT_ERROR,
		TEXT_SAND,
		TEXT_DIRT,
		TEXT_GRASS,
		TEXT_WATER,
		TEXT_ROCK,
		TEXT_MOUNTAIN,
		TEXT_CHARACTER,
		TEXT_TREE1,
		TEXT_TREE2, 
		TEXT_TREE3,
		TEXT_ROCK_O,
		TEXT_GRASS_O,
		TEXT_STICK_BUSH,
		TEXT_BERRY_BUSH
	};

	struct TexturePack
	{
		std::shared_ptr<GE::Graphics::Texture> text;
		int textWidth, textHeight;
		glm::fvec3 textOffset;
		bool operator==(const TexturePack other);
	};

	class TexturePacks
	{
	public:
		static TexturePack get(TextureNameEnums e) { 
			if (!initialized)
			{
				init();
			}
			return map.at(e);
		};
		static void init();
	private:
		static inline const std::string TEXTURE_FILEPATH = "res\\textures\\";
		static inline bool initialized = false;
		static inline std::unordered_map<TextureNameEnums, TexturePack> map = {};
	};
}