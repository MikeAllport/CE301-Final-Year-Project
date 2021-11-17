#ifndef APP_WORLDGEN_MAPGEN
#define APP_WORLDGEN_MAPGEN
#include <gepch.h>
#include <App/WorldGeneration/World.h>
#include <App/WorldGeneration/GeneratorSettings.h>

namespace App::WorldGen
{
	class MapGenerator
	{
	public:
		MapGenerator(App::World& world, WorldGen::MapSettings& settings);

		std::vector<std::vector<float>> generateMap();
	private:
		void applySymmetry(std::vector<std::vector<float>>& map, Noise* noise);
		void applyNoiseSharpening(std::vector<std::vector<float>>& map, float power);
		void distanceNoise(std::vector<std::vector<float>>& map);
		void resetMapRange(std::vector<std::vector<float>>& map);
		World& world;
		WorldGen::MapSettings& settings;
	};
	float convertRange0to1(float value, float min, float max);
};

#endif