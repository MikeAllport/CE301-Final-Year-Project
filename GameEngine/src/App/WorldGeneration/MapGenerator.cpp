#include <gepch.h>
#include <App/WorldGeneration/MapGenerator.h>

namespace App::WorldGen
{
	float convertRange0to1(float value, float min, float max)
	{
		return App::convertRange0to1(value, min, max);
	}

	MapGenerator::MapGenerator(App::World& world, WorldGen::MapSettings& settings):
		world(world),
		settings(settings)
	{
	}

	std::vector<std::vector<float>> MapGenerator::generateMap()
	{
		std::unique_ptr<Noise> dsNoiseGen;
		if (settings.USE_PERLIN)
		{
			dsNoiseGen = std::unique_ptr<Noise>(new Perlin(world.getRNG(), world.tileMapCol));
		}
		else
		{
			settings.FREQUENCY = 1.0f;
			dsNoiseGen = std::unique_ptr<Noise>(new DiamondSquare(world.rng, world.tileMapCol, settings.NOISE_ROUGHNESS, settings.ROUGHNESS_DIV, settings.USE_MORE_WATER));
		}

		std::vector<std::vector<float>> map(world.tileMapRow, std::vector<float>(world.tileMapRow));
		// smooth noise
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float elevation = dsNoiseGen->noise(i * settings.FREQUENCY, j * settings.FREQUENCY);
				map[i][j] = elevation;
			}
		resetMapRange(map);
		if (!settings.USE_PURE_NOISE)
		{
			if (settings.USE_SYMMETRY)
				applySymmetry(map, dsNoiseGen.get());
			applyNoiseSharpening(map, settings.REDIST_EXPON);
			// apply distance function to give more islandy shape, areas closer to centre
			// get raised, areas further from centre get lowere
			if (settings.USE_DIST_RANGE)
				distanceNoise(map);
			if (settings.USE_DIST_EXP)
				applyNoiseSharpening(map, settings.DIST_EXPON);
		}
		return map;
	}

	void MapGenerator::resetMapRange(std::vector<std::vector<float>>& map)
	{
		float max = INT_MIN;
		float min = INT_MAX;
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float elevation = map[i][j];
				max = std::max(max, elevation);
				min = std::min(min, elevation);
			}
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float elevation = map[i][j];
				map[i][j] = convertRange0to1(elevation, min, max);
			}
	}

	void MapGenerator::applySymmetry(std::vector<std::vector<float>>& map, Noise* dsNoiseGen)
	{
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float elevation = map[i][j];
				elevation += 0.5 * dsNoiseGen->noise(settings.SYMMETRY_FACTOR * i * settings.FREQUENCY, settings.SYMMETRY_FACTOR * j * settings.FREQUENCY);
				elevation += 0.25 * dsNoiseGen->noise(settings.SYMMETRY_FACTOR * 2 * i * settings.FREQUENCY, settings.SYMMETRY_FACTOR * 2 * j * settings.FREQUENCY);
				map[i][j] = elevation;
			}
		resetMapRange(map);
	}

	void MapGenerator::applyNoiseSharpening(std::vector<std::vector<float>>& map, float power)
	{
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float elevation = map[i][j];
				elevation = std::pow(elevation, power);
				map[i][j] = elevation;
			}
		resetMapRange(map);
	}

	void MapGenerator::distanceNoise(std::vector<std::vector<float>>& map)
	{
		for (int i = 0; i < world.tileMapCol; ++i)
			for (int j = 0; j < world.tileMapCol; j++)
			{
				float distX = (j / (float)(world.tileMapCol - 1)) - 0.5f;
				float distY = (i / (float)(world.tileMapRow - 1)) - 0.5f;
				distX *= settings.DIST_FACT;
				distY *= settings.DIST_FACT;
				float maxDist = 0.5 * settings.DIST_FACT;
				float dist = std::sqrt(distX * distX + distY * distY) / std::sqrt(0.5);
				dist / std::sqrt(maxDist);
				float elevation = (1 + map[i][j] - dist) / 2.f;
				map[i][j] = elevation;
			}
		resetMapRange(map);
	}
}