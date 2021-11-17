#include <gepch.h>
#include "Tile.h"

#define _CRTDBG_MAP_ALLOC

namespace App
{
	bool Tile::USE_GREYSCALE = false;
	Tile::Tile(glm::fvec3& position) :
		GameObject(position, glm::vec3(TILE_WIDTH, 0, TILE_HEIGHT)),
		textType(0),
		sprite(this)
	{
		sprite.setOffset(glm::fvec3(TILE_HEIGHT / 2.F, 0, TILE_HEIGHT / 2.F));
	}

	Tile::Tile(const Tile& other) :
		GameObject(other.position, other.size),
		textType(other.textType),
		sprite(this)
	{
		sprite.offset = other.sprite.offset;
	}

	Sprite& Tile::getSprite()
	{
		return sprite;
	}

	void Tile::setTextureType(float type)
	{
		textType = type;	
		TextureNameEnums textName;
		if (type < WATER)
		{
			textName = TEXT_WATER;
		}
		else if (type < SAND)
		{
			textName = TEXT_SAND;
		}
		else if (type < DIRT)
		{
			textName = TEXT_DIRT;
		}
		else if (type < GRASS)
		{
			textName = TEXT_GRASS;
		}
		else textName = TEXT_ROCK;
		sprite.setTexture(textName);
	}

	float Tile::getTextureType()
	{
		return textType;
	}

	int Tile::getWidth()
	{
		return TILE_WIDTH;
	}

	int Tile::getHeight()
	{
		return TILE_HEIGHT;
	}


	void Tile::useGreyscale(bool yn)
	{
		USE_GREYSCALE = yn;
	}

	void Tile::draw(GE::Graphics::Renderer& rend)
	{
		if (Tile::USE_GREYSCALE)
		{
			sprite.setModelMatrix(rend);
			rend.drawStaticQuadColored(glm::vec4(textType, textType, textType, 1));
		}
		else
		{
			sprite.setModelMatrix(rend);
			rend.drawStaticQuadTextured(sprite.textPack.text);
		}
	}
}