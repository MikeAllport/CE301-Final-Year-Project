#ifndef GAME_WORLD
#define GAME_WORLD

#include <App/Random.h>
#include <App/WorldGeneration/Tile.h>
#include <App/Interfaces.h>
#include <App/WorldGeneration/Noise.h>
#include <App/WorldGeneration/GeneratorSettings.h>

namespace App
{
	namespace WorldGen
	{
		extern class MapGenerator;
	}
	class World : public IDrawable
	{
	public:
		World(int size);
		~World();
		void draw(GE::Graphics::Renderer& rc) override;
		void drawStaticContent(GE::Graphics::Renderer& rc);
		void generateWorld(WorldGen::MapSettings settings = WorldGen::MapSettings());
		Tile& getTileFromXY(int x, int y);
		Random& getRNG();
		Random rng;
		int SEED = 0;
		float sizex, sizey;
	private:
		friend class App::WorldGen::MapGenerator;
		
		// uses contiguous block of memory for 2d array
		std::vector<std::vector<Tile>> tilemap;
		int tileMapRow, tileMapCol;

		friend DiamondSquare;
		void populateTilemap();
	};
	float convertRange0to1(float value, float min, float max);
}
#endif