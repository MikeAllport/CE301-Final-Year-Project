#include "gepch.h"
#include "TextureMap.h"

namespace App
{
	void TexturePacks::init()
	{
		GE::Graphics::TextureCache::init(TEXTURE_FILEPATH);
		map[TEXT_ERROR] =
		{
			GE::Graphics::TextureCache::getTexture("textureError.png"),
			512,
			512,
			{0,0,0}
		};
		map[TEXT_SAND] =
		{
			GE::Graphics::TextureCache::getTexture("sand.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_DIRT] =
		{
			GE::Graphics::TextureCache::getTexture("dirt.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_GRASS] =
		{
			GE::Graphics::TextureCache::getTexture("grass.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_WATER] =
		{
			GE::Graphics::TextureCache::getTexture("water.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_ROCK] =
		{
			GE::Graphics::TextureCache::getTexture("rock.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_MOUNTAIN] =
		{
			GE::Graphics::TextureCache::getTexture("mountain.png"),
			2048,
			2048,
			{0,0,0}
		};
		map[TEXT_CHARACTER] =
		{
			GE::Graphics::TextureCache::getTexture("testCharacter.png"),
			600,
			500,
			{0,56,0}
		};
		map[TEXT_TREE1] =
		{
			GE::Graphics::TextureCache::getTexture("tree1.png"),
			1028,
			1028,
			{0,0,0}
		};
		map[TEXT_TREE2] =
		{
			GE::Graphics::TextureCache::getTexture("tree2.png"),
			1028,
			1028,
			{0,0,0}
		};
		map[TEXT_TREE3] =
		{
			GE::Graphics::TextureCache::getTexture("tree3.png"),
			1028,
			1028,
			{0,0,0}
		};
		map[TEXT_BERRY_BUSH] =
		{
			GE::Graphics::TextureCache::getTexture("berry_bush.png"),
			1028,
			1028,
			{0,0,0}
		};
		map[TEXT_GRASS_O] =
		{
			GE::Graphics::TextureCache::getTexture("grass_o.png"),
			1028,
			1028,
			{0,224,0}
		};
		map[TEXT_ROCK_O] =
		{
			GE::Graphics::TextureCache::getTexture("rock_o.png"),
			512,
			512,
			{0,0,0}
		};
		map[TEXT_STICK_BUSH] =
		{
			GE::Graphics::TextureCache::getTexture("stick_bush.png"),
			1028,
			1028,
			{0,80,0}
		};
		initialized = true;
	}
	bool TexturePack::operator==(const TexturePack other)
	{
		return text == other.text && textWidth == other.textWidth
			&& textHeight == other.textHeight && textOffset == other.textOffset;
	}
}
