#include <gepch.h>
#include "World.h"
#include <App/WorldGeneration/MapGenerator.h>

#define _CRTDBG_MAP_ALLOC

namespace App
{
	float convertRange0to1(float value, float min, float max)
	{
		float oldRange = max - min;
		float newRange = 1;
		float newValue = ((value - min) * 1) / oldRange;
		return newValue;
	}

	World::World(int size) :
		rng()
	{
		float sizeCheck = size;
		while (sizeCheck > 1)
			sizeCheck /= 2.0f;
		if (sizeCheck < 0)
		{
			GE_WARN("Error initializing world with invalid size, using 1028 as default");
			sizeCheck = 1028;
		}
		else sizeCheck = size;
		tileMapCol = sizeCheck + 1;
		tileMapRow = sizeCheck + 1;
		sizex = tileMapCol * Tile::TILE_WIDTH;
		sizey = tileMapRow * Tile::TILE_HEIGHT;
		populateTilemap();
	}

	Random& World::getRNG()
	{
		return rng;
	}

	Tile& World::getTileFromXY(int x, int y)
	{
		if (x / sizex > 1 || y / sizey > 1)
		{
			GE_WARN("{} Tile requested with coords greater than world size. Posx: {}, PosY {}",
				typeid(*this).name(), x, y);
			return tilemap[0][0];
		}
		x /= Tile::TILE_WIDTH;
		y /= Tile::TILE_HEIGHT;
		return tilemap[y][x];
	}

	void World::generateWorld(WorldGen::MapSettings settings)
	{
		if (settings.USE_RANDOM_SEED)
		{
			rng = Random();
			SEED = rng.getSeed();
		}
		else rng = Random(SEED);
		if (settings.USE_DEFAULTS)
			settings = WorldGen::MapSettings();

		WorldGen::	MapGenerator generator(*this, settings);
		std::vector<std::vector<float>> map1 = generator.generateMap();
		
		Tile::useGreyscale(settings.USE_GREYSCALE);
		if (settings.USE_MULTI_LAYERED)
		{
			std::vector<std::vector<float>> map2 = generator.generateMap();
			for (int i = 0; i < tileMapCol; ++i)
				for (int j = 0; j < tileMapCol; j++)
				{
					float elevation = std::max({ map1[i][j], map2[i][j] });
					map1[i][j] = elevation;
				}
		}
		for (int i = 0; i < tileMapCol; ++i)
			for (int j = 0; j < tileMapCol; j++)
			{
				tilemap[i][j].setTextureType(map1[i][j]);
			}
	}

	void World::populateTilemap()
	{
		tilemap = std::vector<std::vector<Tile>>(tileMapCol);
		for (auto vector : tilemap)
		{
			vector.reserve(tileMapCol);
		}
		for (int i = 0; i < tileMapCol * tileMapRow; ++i)
		{
			int x = (i % tileMapCol);
			int posX = x * Tile::TILE_WIDTH;
			int y = (i / tileMapCol);
			int posY = y * Tile::TILE_HEIGHT;
			glm::fvec3 position(posX, 0, posY);
			tilemap[y].push_back(Tile(position));
		}
	}

	void World::drawStaticContent(GE::Graphics::Renderer& rc)
	{
		for (auto i = 0; i < tileMapCol * tileMapRow; ++i)
		{
			int x = (i % tileMapCol);
			int y = (i / tileMapCol);
			tilemap[y][x].draw(rc);
		}
	}

	void World::draw(GE::Graphics::Renderer& rc)
	{
	}

	World::~World()
	{
	}
}