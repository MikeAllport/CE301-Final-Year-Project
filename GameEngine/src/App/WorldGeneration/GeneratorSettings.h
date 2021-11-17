#pragma once
namespace App::WorldGen
{
	struct MapSettings
	{
		float NOISE_ROUGHNESS = 500;
		float REDIST_EXPON = 3, DIST_EXPON = 5, DIST_FACT = 2, ROUGHNESS_DIV = 0.5, FREQUENCY = 1,
			SYMMETRY_FACTOR = 2;
		bool USE_DIST_RANGE = true, USE_MORE_WATER = false, USE_SYMMETRY = true, USE_DEFAULTS = true,
			USE_RANDOM_SEED = true, USE_DIST_EXP = true, USE_PURE_NOISE = false, USE_GREYSCALE = false,
			USE_MULTI_LAYERED = true, USE_PERLIN = false;
	};
	struct ObjectPlacementSettings
	{
		int minDist = 150,
			maxDist = 800,
			attempts = 20,
			cellRadius = 50,
			blueNoise = 15;
		bool useHeatMap = false;
	};
}